#
# Image
#

class Image:
    def __init__(self, w, h, data):
        assert isinstance(w, int)
        assert isinstance(h, int)
        assert isinstance(data, list)

        self.__width = w
        self.__height = h
        self.r = []
        self.g = []
        self.b = []
        if len(data) == w*h:
            self.r = data
        elif len(data) == w*h*3:
            for i in range(w*h):
                self.r.append(data[i*3])
                self.g.append(data[i*3+1])
                self.b.append(data[i*3+2])

    def width(self):
        return self.__width

    def height(self):
        return self.__height

    def get_pixel(self, y, x):
        assert isinstance(x, int)
        assert isinstance(y, int)
        assert y < self.__height
        assert x < self.__width

        if self.g or self.b:
            return (self.r[y*self.__width + x], self.g[y*self.__width + x], self.b[y*self.__width + x])
        else:
            color = self.r[y*self.width + x]
            return (color, color, color)

