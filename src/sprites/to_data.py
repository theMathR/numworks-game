from PIL import Image

fn = "src/sprites/toriel.png"
im = Image.open(fn)

data = [im.size[0], im.size[1]]
coloring = False
count = 0

for y in range(data[1]):
    for x in range(data[0]):
        _,_,_,a = im.getpixel((x,y))
        if bool(a) != coloring:
            coloring = not coloring
            data.append(count)
            count = 1
        else:
            count += 1
print('{'+','.join(map(str,data))+'}')
print(len(data))
