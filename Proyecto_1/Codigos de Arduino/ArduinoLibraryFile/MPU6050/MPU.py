import math
import OpenGL.GL as gl
import OpenGL.GLU as glu
import pygame
import pygame.locals
import serial


class Vector(object):
    def __init__(self, x=0, y=0, z=0):
        self.x = x
        self.y = y
        self.z = z


class MPU(object):
    def __init__(self, serial_port='COM5', baud_rate=9600):
        self.serial = serial.Serial(serial_port, baud_rate)
        self.accelerometer = Vector()
        self.gyroscope = Vector()
        self.temperature = int()

    def __read_data(self):
        return [float(x) for x in self.serial.readline().split(',')]

    def __distance(self, a, b):
        return math.sqrt((a*a)+(b*b))

    def __x_rotation(self, vec):
        xz_distance = self.__distance(vec.x, vec.z)
        radians = math.atan2(vec.y, xz_distance)
        return math.degrees(radians)

    def __y_rotation(self, vec):
        yz_distance = self.__distance(vec.y, vec.z)
        radians = math.atan2(vec.x, yz_distance)
        return -math.degrees(radians)

    def update(self):
        aX, aY, aZ, gX, gY, gZ, temp = self.__read_data()
        self.accelerometer = Vector(aX, aY, aZ)
        self.gyroscope = Vector(gX, gY, gZ)
        self.temperature = temp

    def get_rotation(self):
        x_rotation = self.__x_rotation(self.accelerometer)
        y_rotation = self.__y_rotation(self.accelerometer)
        return [x_rotation, y_rotation]


class Visualization(object):
    def __init__(self, window_width=800, window_height=600):
        pygame.init()
        pygame.display.set_caption('MPU')
        pygame.display.set_mode((window_width, window_height),
            pygame.locals.HWSURFACE | pygame.locals.OPENGL | pygame.locals.DOUBLEBUF)
        
        # Configure window related properties.
        gl.glViewport(0, 0, window_width, window_height)
        gl.glMatrixMode(gl.GL_PROJECTION)
        gl.glLoadIdentity()
        glu.gluPerspective(45.0, float(window_width) / window_height, 0.001, 10.0)
        gl.glMatrixMode(gl.GL_MODELVIEW)
        gl.glLoadIdentity()
        glu.gluLookAt(0.0, 1.0, -5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0)

        # Configure graphical related properties.
        gl.glEnable(gl.GL_DEPTH_TEST)
        gl.glClearColor(0.0, 0.0, 0.0, 0.0)
        gl.glShadeModel(gl.GL_SMOOTH)
        gl.glEnable(gl.GL_BLEND)
        gl.glEnable(gl.GL_POLYGON_SMOOTH)
        gl.glHint(gl.GL_POLYGON_SMOOTH_HINT, gl.GL_NICEST)
        gl.glEnable(gl.GL_COLOR_MATERIAL)
        gl.glEnable(gl.GL_LIGHTING)
        gl.glEnable(gl.GL_LIGHT0)
        gl.glLightfv(gl.GL_LIGHT0, gl.GL_AMBIENT, (0.3, 0.3, 0.3, 1.0))

    def __render_background(self):
        gl.glColor((1, 1, 1))
        gl.glLineWidth(1)
        gl.glBegin(gl.GL_LINES)
        for x in range(-20, 22, 2):
            gl.glVertex3f(x/10., -1, -1)
            gl.glVertex3f(x/10., -1, 1)
        for x in range(-20, 22, 2):
            gl.glVertex3f(x/10., -1, 1)
            gl.glVertex3f(x/10., 1, 1)
        for z in range(-10, 12, 2):
            gl.glVertex3f(-2, -1, z/10.)
            gl.glVertex3f( 2, -1, z/10.)
        for z in range(-10, 12, 2):
            gl.glVertex3f(-2, -1, z/10.)
            gl.glVertex3f(-2,  1, z/10.)
        for z in range(-10, 12, 2):
            gl.glVertex3f( 2, -1, z/10.)
            gl.glVertex3f( 2,  1, z/10.)
        for y in range(-10, 12, 2):
            gl.glVertex3f(-2, y/10., 1)
            gl.glVertex3f( 2, y/10., 1)
        for y in range(-10, 12, 2):
            gl.glVertex3f(-2, y/10., 1)
            gl.glVertex3f(-2, y/10., -1)
        for y in range(-10, 12, 2):
            gl.glVertex3f(2, y/10., 1)
            gl.glVertex3f(2, y/10., -1)
        gl.glEnd()

    def __render_cube(self):
        vertices = [
            (-1.0, -0.05, 0.5),
            (1.0, -0.05, 0.5),
            (1.0, 0.05, 0.5),
            (-1.0, 0.05, 0.5),
            (-1.0, -0.05, -0.5),
            (1.0, -0.05, -0.5),
            (1.0, 0.05, -0.5),
            (-1.0, 0.05, -0.5)
        ]
        normals = [
            (0.0, 0.0, +1.0), # front
            (0.0, 0.0, -1.0), # back
            (+1.0, 0.0, 0.0), # right
            (-1.0, 0.0, 0.0), # left
            (0.0, +1.0, 0.0), # top
            (0.0, -1.0, 0.0)  # bottom
        ]
        indices = [
            (0, 1, 2, 3), # front
            (4, 5, 6, 7), # back
            (1, 5, 6, 2), # right
            (0, 4, 7, 3), # left
            (3, 2, 6, 7), # top
            (0, 1, 5, 4)  # bottom
        ]
        gl.glColor((.5, .5, .5))
        gl.glBegin(gl.GL_QUADS)
        for face in xrange(6):
            gl.glNormal3dv(normals[face])
            v1, v2, v3, v4 = indices[face]
            gl.glVertex(vertices[v1])
            gl.glVertex(vertices[v2])
            gl.glVertex(vertices[v3])
            gl.glVertex(vertices[v4])
        gl.glEnd()

    def run(self):
        mpu = MPU()

        while True:
            for event in pygame.event.get():
                if event.type == pygame.locals.QUIT:
                    return

            mpu.update()
            x_angle, y_angle = mpu.get_rotation()

            gl.glClear(gl.GL_COLOR_BUFFER_BIT | gl.GL_DEPTH_BUFFER_BIT)
            self.__render_background()
            gl.glPushMatrix()
            gl.glRotate(float(x_angle), 1, 0, 0)
            gl.glRotate(-float(y_angle), 0, 0, 1)
            self.__render_cube()
            gl.glPopMatrix()
            pygame.display.flip()


if __name__ == "__main__":
    Visualization().run()
