#
# Image
#

class Image:
    """Holds image as a list of floats

    Holds separate list for R, G and B channels. If image is
    b&w or grayscale G and B lists are empty and don't
    consume memory"""

    def __init__(self, w, h, data):
        """Creates image from list of floats

        Supplied image can be grayscale or color. See code for explanation of how
        data is stored

        Signature: f(int, int, list[float]) -> Image"""
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
        """Returns image width in pixels

        Signature: f(None) -> int"""
        return self.__width

    def height(self):
        """Returns image height in pixels

        Signature: f(None) -> int"""
        return self.__height

    def get_pixel(self, y, x):
        """Get average float value of pixel. Addresing is in [row; col] format

        This function is actual only in colorful images. It allows
        for algorithms for grayscale images to also work with color images

        Signature: f(int, int) -> float"""
        assert isinstance(x, int)
        assert isinstance(y, int)
        assert y < self.__height
        assert x < self.__width

        if self.g or self.b:
            return (self.r[y*self.__width + x], self.g[y*self.__width + x], self.b[y*self.__width + x])
        else:
            color = self.r[y*self.width + x]
            return (color, color, color)

