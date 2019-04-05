import sys
import svgpath.parser as parser

C_STUB_FILENAME = "stub.c"


def genArray(filename, tolerance=0.1):
    superpaths = parser.getPathsFromSVGFile(filename)
    height = superpaths[1].imag

    pointcounter = 0
    polycounter = 0

    polycode = bytearray("struct polygon polys[NUMPOLYS] = {\n", "utf-8")
    pointcode = bytearray("float pointcloud[NUMPOINTS*2] = {\n", "utf-8")

    for superpath in superpaths[0]:
        for path in superpath.breakup():

            linearPath = path.linearApproximation(error=tolerance)
            polylength = 0

            polycode += bytearray(
                "{"+"\n\t.startpoint = {}, \n".format(pointcounter), "utf-8")
            for line in linearPath:

                start_y = str(height-line.start.imag)
                start_x = str(line.start.real)

                pointcode += bytearray(
                    "\t{}f, {}f,\n".format(start_x, start_y),"utf-8")

                pointcounter += 1
                polylength += 1
            red, green, blue = superpath.svgState.fill
            polycode += bytearray(
                """\t.numpoints = {},
\t.red = {},
\t.green = {},
\t.blue = {}\n""".format(
    polylength, int(red*255), int(green*255), int(blue*255)), "utf-8")
            polycode += bytearray("},\n", "utf-8")
            polycounter += 1

    pointcode = pointcode[:-2] + bytearray("\n};", "utf-8")
    polycode = polycode[:-2] + bytearray("};\n", "utf-8")

    print("#define NUMPOLYS " + str(polycounter))
    print(polycode.decode())
    print("#define NUMPOINTS " + str(pointcounter))
    print(pointcode.decode())


if __name__ == '__main__':
    if len(sys.argv) < 2:
        print("usage:\n\tpython3 {} SVG_IMAGE > C_SOURCE".format(
            sys.argv[0]), file=sys.stderr)
        sys.exit(1)

    svg_filename = sys.argv[1]
    with open(C_STUB_FILENAME, 'r') as stub:
        in_section = False
        for line in stub:
            if "DATA SECTION BEGIN" in line:
                print(line, end="")
                genArray(svg_filename)
                in_section = True
            if "DATA SECTION END" in line:
                in_section = False
            if not in_section:
                print(line, end="")
