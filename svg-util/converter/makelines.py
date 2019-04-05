import sys
import svgpath.parser as parser

def genDrawline(filename, tolerance=0.1, strokeAll = False):
    superpaths = parser.getPathsFromSVGFile(filename)
    height = superpaths[1].imag
    width = superpaths[2].real
    for superpath in superpaths[0]:
        for path in superpath.breakup():
            linearPath = path.linearApproximation(error=tolerance)
            for line in linearPath:
                start_y = str(1-(line.start.imag / height))
                start_x = str(line.start.real / width)
                end_y   = str(1-(line.end.imag / height))
                end_x   = str(line.end.real / width)
                print("graphics_drawline("  + start_x + "*size_y," + start_y + "*size_x," + end_x + "*size_y," + end_y + "*size_x, textcol);")

if __name__ == '__main__':
    genDrawline(sys.argv[1])
