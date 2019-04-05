import sys
import svgpath.parser as parser

C_STUB_FILENAME = "stub.c"


def genArray(filename, tolerance=0.1, strokeAll=False):
    superpaths = parser.getPathsFromSVGFile(filename)
    height = superpaths[1].imag
    width = superpaths[2].real

    pointcounter = 0
    polycounter = 0

    polycode = bytearray("struct polygon polys[NUMPOLYS] = {\n", "utf-8")
    pointcode = bytearray("float pointcloud[NUMPOINTS*2] = {\n", "utf-8")

    for superpath in superpaths[0]:
        for path in superpath.breakup():

            linearPath = path.linearApproximation(error=tolerance)
            polylength = 0

            polycode = polycode + \
                bytearray("{\n\t.startpoint = " +
                          str(pointcounter) + ",\n",    "utf-8")
            for line in linearPath:

                start_y = str(height-line.start.imag)
                start_x = str(line.start.real)
                end_y = str(height-line.end.imag)
                end_x = str(line.end.real)

                pointcode = pointcode + \
                    bytearray("\t" + str(start_x) + "f, " +
                              str(start_y) + "f,\n", "utf-8")

                pointcounter += 1
                polylength += 1
            # else:
            #     pointcode = pointcode + bytearray("\t" + str(end_x) + "f, " + str(end_y) + "f,\n","utf-8")
            red,green,blue = superpath.svgState.fill
            polycode = polycode + bytearray("\t.numpoints = "         + str(polylength)     + ",\n",    "utf-8")
            polycode = polycode + bytearray("\t.red = "               + str(red  *255)      + ",\n",    "utf-8")
            polycode = polycode + bytearray("\t.green = "             + str(green*255)      + ",\n",    "utf-8")
            polycode = polycode + bytearray("\t.blue = "              + str(blue *255)      + ",\n},\n","utf-8")
            
            polycounter = polycounter + 1

    
    pointcode = pointcode[:-2] + bytearray("\n};","utf-8")
    
    print("#define NUMPOLYS " + str(polycounter))

    polycode = polycode[:-2]
    polycode = polycode + bytearray("};\n","utf-8")
    print(polycode.decode())

    print("#define NUMPOINTS " + str(pointcounter))
    print(pointcode.decode())


if __name__ == '__main__':
    if (len(sys.argv) < 2):
        print("usage:\n\tpython3 {} SVG_IMAGE > C_SOURCE".format(
            sys.argv[0]), file=sys.stderr)
        sys.exit(1)

    svg_filename = sys.argv[1]
    with open(C_STUB_FILENAME,'r') as stub:
        in_data_section = False
        for line in stub:
            if "DATA SECTION BEGIN" in line:
                print(line,end="")
                genArray(svg_filename)
                in_data_section = True
            if "DATA SECTION END" in line:
                in_data_section = False
            if not in_data_section:
                print(line,end="")