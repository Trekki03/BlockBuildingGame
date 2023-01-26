
namespace engine::primitives
{
    /*
     * Front Side
     * Right Side
     * Back  Side
     * Left  Side
     * Bottom
     * Top
     *
     * 4 Vertices per Side
     *
     * Vertices Date:
     * PosX, PosY, PosZ, NormX, NormY, NormZ
     */
    float cubeVertices[] = {

            //Front
            -0.5f,    -0.5f,  0.5f,   0.0f,   0.0f,   1.0f,       //0
            0.5f,     -0.5f,  0.5f,   0.0f,   0.0f,   1.0f,     // 1
            0.5f,     0.5f,   0.5f,   0.0f,   0.0f,   1.0f, // 2
            -0.5f,    0.5f,   0.5f,   0.0f,   0.0f,   1.0f,     // 3

            //Right Side
            0.5f,     -0.5f,  0.5f,   1.0f,   0.0f,   0.0f,     // 4
            0.5,      -0.5f,  -0.5f,  1.0f,   0.0f,   0.0f,     // 5
            0.5f,     0.5f,   -0.5f,  1.0f,   0.0f,   0.0f,      // 6
            0.5f,     0.5f,   0.5f,   1.0f,   0.0f,   0.0f,      // 7

            //Back
            0.5f,     -0.5f,  -0.5f,  0.0f,   0.0f,   -1.0f,     // 8
            -0.5f,    -0.5f,  -0.5f,  0.0f,   0.0f,   -1.0f,     // 9
            -0.5f,    0.5f,   -0.5f,  0.0f,   0.0f,   -1.0f,     // 10
            0.5f,     0.5f,   -0.5f,  0.0f,   0.0f,   -1.0f,     // 11

            //Left Side
            -0.5f,    -0.5f,  -0.5f,  -1.0f,  0.0f,   0.0f,   // 12
            -0.5f,    -0.5f,  0.5f,   -1.0f,  0.0f,   0.0f,      // 13
            -0.5f,    0.5f,   0.5f,   -1.0f,  0.0f,   0.0f,     // 14
            -0.5f,    0.5f,   -0.5f,  -1.0f,  0.0f,   0.0f,      // 15

            //Bottom
            0.5f,     -0.5f,  -0.5f,  0.0f,   -1.0f,  0.0f,     // 16
            -0.5f,    -0.5f,  -0.5f,  0.0f,   -1.0f,  0.0f,      // 17
            -0.5f,    -0.5f,  0.5f,   0.0f,   -1.0f,  0.0f,      // 18
            0.5f,     -0.5f,  0.5f,   0.0f,   -1.0f,  0.0f,     // 19

            //Top
            -0.5f,    0.5f,   0.5f,   0.0f,   1.0f,   0.0f,      // 20
            0.5f,     0.5f,   0.5f,   0.0f,   1.0f,   0.0f,      // 21
            0.5f,     0.5f,   -0.5f,  0.0f,   1.0f,   0.0f,      // 22
            -0.5f,    0.5f,   -0.5f,  0.0f,   1.0f,   0.0f     // 23
    };

    /*
     * Front Side
     * Right Side
     * Back  Side
     * Left  Side
     * Bottom
     * Top
     *
     * 6 Indices per Side
     *
     */
    unsigned int cubeIndices[] = {

            //Front
            0,   1,   3,
            1,   2,   3,

            //Right Side
            4,   5,   7,
            5,   6,  7,

            //Back
            8,  9,  11,
            9,  10, 11,

            //Left Side
            12, 13, 15,
            13, 14, 15,

            //Bottom
            16, 17, 19,
            17, 18, 19,

            //Top
            20, 21, 23,
            21, 22, 23
    };
}
