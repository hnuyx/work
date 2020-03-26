from distutils.core import setup
from Cython.Build import cythonize
setup(
    ext_modules = cythonize("Hello.py",language_level = 3, build_dir = 'BUILD_DIR' )
    #ext_modules = cythonize("mpi.pyx", build_dir = 'BUILD_DIR' )
)
