The project is aimed toward support of neural network topologies of any type.
At the moment pann library is capable of running feedforward propagation and least mean square learning algorithm on any network.
You construct network step by step and library can train it, visualize it in 3D(using Qt OpenGL).
All algorithms of propagation(feedforward and training) are done in parallel, depending on processor count or your settings.
Library uses Boost and Qt4. All external dependencies are kept as small as possible. Now all you need for functioning is boost. Qt4 is optional and used only for small visualization utility - pann\_viewer.
There are also a lot of programs. Most interesting is face finder. It constructs Convolution neural networks and trains it to distinguish between face/not-face.

Development platform: CMake, Linux, MS Windows

External dependencies: boost thread, boost date-time(only on windows), boost serialization, pthread(only linux), boost MPI(optional), qt4 (optional)

For more details look wiki and doxygen comments in source code :)
Comments and questiones are much appreciated.