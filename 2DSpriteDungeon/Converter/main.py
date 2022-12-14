import os
import sys
from os import listdir
from PIL import Image

png_folder_dir = r"C:\Users\Brenton\source\repos\Game140\FinalProject\2DSpriteDungeon\Assests\LegendOfZeldaSprites\Link\Death\Png"
bmp_folder_dir = r"C:\Users\Brenton\source\repos\Game140\FinalProject\2DSpriteDungeon\Assests\LegendOfZeldaSprites\Link\Death\Bmp"

#os.mkdir(bmp_folder_dir) 
def png_to_bitmap(file_path_in, file_path_out):
        img = Image.open(file_path_in)
        result = img.quantize(colors=256, method =2)
        result.save(file_path_out)

for images in os.listdir(png_folder_dir):
        file_path = os.path.join(png_folder_dir, images)
        new_file_path = os.path.join(bmp_folder_dir, images[:-4] + ".bmp")
        png_to_bitmap(file_path, new_file_path)
        #print(color_png)