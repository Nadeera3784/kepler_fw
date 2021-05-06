from PIL import Image
import math

# This script opens up a image file that contains a single or multiple images
# and parses through the images & coverts them into a hex array to be used in C code.
# The spacing between characters in image must be consistent and all must have same width or white space around them AND height!!
# Example:
#  ----x-----xxxxxx-- ^
#  --x---x---x-----x- |
#  --xxxxx---xxxxxx-- 5
#  -x-----x--x-----x- |
#  -x-----x--xxxxxx-- v
#  <---9---><---9--->
# Lets say the image above "example.jpg" contains two letters we want to convert to hex.
# We can see the "char_width" for this image is 9. This includes 1 pixel white space on both sides of the letters.
# The "char_height" would be 5 and the number of characters in this image is 2.
# Thats it!

# ONLY EDIT THESE FIELDS
 # Filename containing the images
filename = "text_from.pbm"
# Filename of the output file containing the array
outputFile = "output_array.c"
# The width of each character
char_width = 96#9
# The height of each character
char_height = 39# 5
# Number of characters in the image
num_chars = 1
# Name to give the array
arr_name = "custom-arr"
# Additional notes added to top of array if necessary.
notes = ""                             
# Names that get commented at the end of each element of the array. Can be of any length
names = ["test", "", "", "", "", "", "", "", "", ""]



#DO NOT EDIT.
char_shift = 0
char_count = 0
image = Image.open(filename)
pixels = image.load()
byte_rows = math.ceil(char_height / 8)
byte_data = ''
image_data = []

testDraw=[]


outputFile = open(outputFile, "w")
if(len(notes)>0):
    outputFile.write("/*\n****NOTES****\n" + notes + "\n*/\n")
outputFile.write("// page size: " + str(byte_rows) + "\n")
outputFile.write("const uint8_t " + arr_name + "_" + str(char_width)+"x" + str(char_height) + "[" + str(num_chars) + "][" + str(byte_rows*char_width) +"] = {")
for chars in range(num_chars):
    outputFile.write("\n\t\t\t{")
    for b_y in range(byte_rows):
        for x in range(char_width):
            byte_data = '' #Reset.
            for y in range(8):
                # print(y)
                try:
                    # if(b_y == 4 and y == 7):
                    #     continue
                    if(pixels[x + char_shift, y + (8*b_y)][1] == 255): # Just check one value because it's either black (0,0,0) or white(255,255,255).
                        byte_data = byte_data + '0'
                    else:
                        byte_data = byte_data + '1'
                except:
                    byte_data = byte_data + '0'
                # print(byte_data)
            hex_value = hex(int(byte_data, 2))
            # print(hex_value)
            image_data.append(hex_value)
            outputFile.write(hex_value)
            testDraw.append(byte_data)
            if((b_y == (byte_rows-1)) and (x == (char_width-1))):
                continue
            else:
                outputFile.write(", ")
            if(x !=0 and x%14==0):
                outputFile.write("\n\t\t\t")
        # outputFile.write("\n\t\t\t")
    #TestDrawings
    drawing=''
    for x in range(char_width):
        for y in range(byte_rows):
            drawing += str(testDraw[x + (char_width*y)])
        drawing+="\n"
    testDraw=[]    
    print(drawing)
    char_shift+=char_width
    if(char_count == num_chars - 1):
        outputFile.write("}")
    else:
        outputFile.write("}, // " + names[char_count])

    char_count+=1

outputFile.write("}; // " + names[char_count-1])
outputFile.close()


