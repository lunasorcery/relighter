relighter
=========

**relighter** is a very experimental CPU pathtracing renderer, built on the idea of capturing bounce data for a scene once, and then being able to change textures and light colors afterwards without re-casting rays.

It consists of two parts, **tracer** and **lighter**. **tracer** performs the ray-testing, streaming captured bounce data out into a file. **lighter** then takes this bounce data file, and resolves it with a set of input textures to generate a final image. Swapping out the textures will generate a differently-lit image from the same captured bounce data.

At present, the filepaths, render configuration, and scene are hardcoded into the two main.cpp files. I intend to move these out into commandline parameters at some point™.