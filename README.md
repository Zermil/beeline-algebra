# beeline-algebra

Linear algebra library inspired by [Handmade Math](https://github.com/HandmadeMath/Handmade-Math) used mostly with [OpenGL](https://www.opengl.org/)

## Notes
- All Matrices are row-major order, so when passing them to OpenGL remember to either transpose the matrix yourself or tell OpenGL to transpose it.

- Anonymous structs inside unions, meaning, most C++ compilers will issue a warning, you can safely ignore it with appropriate compiler flag.