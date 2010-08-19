#include "spec_helper.h"

const float epsilon = 0.000001f;

describe(simd4x4f, "creating") {
    
    it("should be possible to create with params") {
        
        simd4x4f x = simd4x4f_create(simd4f_create(1,  2,  3,  4 ),
                                   simd4f_create(5,  6,  7,  8 ),
                                   simd4f_create(9,  10, 11, 12 ),
                                   simd4f_create(13, 14, 15, 16 ));

        should_be_equal_simd4f( x.x, simd4f_create(1,  2,  3,  4 ) , epsilon);
        should_be_equal_simd4f( x.y, simd4f_create(5,  6,  7,  8 ) , epsilon);
        should_be_equal_simd4f( x.z, simd4f_create(9,  10, 11, 12 ), epsilon);
        should_be_equal_simd4f( x.w, simd4f_create(13, 14, 15, 16 ), epsilon);

        // octave simd4x4f: [1,5,9,13 ; 2,6,10,14 ; 3,7,11,15 ; 4,8,12,16 ]
        should_be_equal_simd4x4f(x, simd4x4f_create(simd4f_create(1.000000, 2.000000, 3.000000, 4.000000), simd4f_create(5.000000, 6.000000, 7.000000, 8.000000), simd4f_create(9.000000, 10.000000, 11.000000, 12.000000), simd4f_create(13.000000, 14.000000, 15.000000, 16.000000)), epsilon );
        
    }
    

    it("should be possible to set to identity") {
        simd4x4f x;
        simd4x4f_identity(&x);
        
        // octave simd4x4f: [1,0,0,0; 0,1,0,0; 0,0,1,0; 0,0,0,1]
        should_be_equal_simd4x4f(x, simd4x4f_create(simd4f_create(1.000000, 0.000000, 0.000000, 0.000000), simd4f_create(0.000000, 1.000000, 0.000000, 0.000000), simd4f_create(0.000000, 0.000000, 1.000000, 0.000000), simd4f_create(0.000000, 0.000000, 0.000000, 1.000000)), epsilon );
    }
}


describe(simd4x4f, "loading and storing") {

    it("should be possible to load from array of 16 floats with simd4x4f_uload") {
        
        simd4x4f x;
        float f[16] = {1,2,3,4, 5,6,7,8, 9,10,11,12, 13,14,15,16 };
        simd4x4f_uload(&x, f);

        should_be_equal_simd4x4f(x, simd4x4f_create( simd4f_create(1,2,3,4),
                                                     simd4f_create(5,6,7,8),
                                                     simd4f_create(9,10,11,12),
                                                     simd4f_create(13,14,15,16) ), epsilon);
        
    }

}


describe(simd4x4f, "matrix utility") {
    
    it("should have simd4x4f_transpose_inplace for transpose") {
        
        simd4x4f x = simd4x4f_create(simd4f_create(1,  2,  3,  4 ),
                                   simd4f_create(5,  6,  7,  8 ),
                                   simd4f_create(9,  10, 11, 12 ),
                                   simd4f_create(13, 14, 15, 16 ));
        
        simd4x4f_transpose_inplace(&x);
        
        // octave simd4x4f: transpose([1,5,9,13 ; 2,6,10,14 ; 3,7,11,15 ; 4,8,12,16 ])
        should_be_equal_simd4x4f(x, simd4x4f_create(simd4f_create(1.000000, 5.000000, 9.000000, 13.000000), simd4f_create(2.000000, 6.000000, 10.000000, 14.000000), simd4f_create(3.000000, 7.000000, 11.000000, 15.000000), simd4f_create(4.000000, 8.000000, 12.000000, 16.000000)), epsilon );
    }

    it("should have simd4x4f_transpose for transpose") {
        
        simd4x4f in = simd4x4f_create(simd4f_create(1,  2,  3,  4 ),
                                   simd4f_create(5,  6,  7,  8 ),
                                   simd4f_create(9,  10, 11, 12 ),
                                   simd4f_create(13, 14, 15, 16 ));
        
        simd4x4f x;
        simd4x4f_transpose(&in, &x);
        
        // octave simd4x4f: transpose([1,5,9,13 ; 2,6,10,14 ; 3,7,11,15 ; 4,8,12,16 ])
        should_be_equal_simd4x4f(x, simd4x4f_create(simd4f_create(1.000000, 5.000000, 9.000000, 13.000000), simd4f_create(2.000000, 6.000000, 10.000000, 14.000000), simd4f_create(3.000000, 7.000000, 11.000000, 15.000000), simd4f_create(4.000000, 8.000000, 12.000000, 16.000000)), epsilon );
    }

    it("should have simd4x4f_matrix_vector_mul for matrix-vector multiply") {
        
        simd4x4f a = simd4x4f_create(simd4f_create( 1,    9,   17,   25 ),
                                     simd4f_create( 3,   11,   19,   27 ),
                                     simd4f_create( 5,   13,   21,   29 ),
                                     simd4f_create( 7,   15,   23,   31 ));

        simd4f b = simd4f_create( 26,  -28,   30,  -32 );
        
        simd4f x;
        simd4x4f_matrix_vector_mul(&a, &b, &x);
        
        // octave simd4f: [1,3,5,7;9,11,13,15;17,19,21,23;25,27,29,31] * [26;-28;30;-32]
        should_be_equal_simd4f(x, simd4f_create(-132.000000, -164.000000, -196.000000, -228.000000), epsilon );
    }

    it("should have simd4x4f_matrix_vector3_mul for matrix-vector3 multiply") {
        
        simd4x4f a = simd4x4f_create(simd4f_create( 1,    9,   17,   25 ),
                                     simd4f_create( 3,   11,   19,   27 ),
                                     simd4f_create( 5,   13,   21,   29 ),
                                     simd4f_create( 7,   15,   23,   31 ));

        simd4f b = simd4f_create( 26,  -28,   30,  -32 );
        
        simd4f x;
        simd4x4f_matrix_vector3_mul(&a, &b, &x);
        
        // TODO octave simd4f: [1,3,5,7;9,11,13,15;17,19,21,23;25,27,29,31] * [26;-28;30;0]
        
    }

    it("should have simd4x4f_matrix_vector3_mul for matrix-vector3 multiply") {
        
        simd4x4f a = simd4x4f_create(simd4f_create( 1,    9,   17,   25 ),
                                     simd4f_create( 3,   11,   19,   27 ),
                                     simd4f_create( 5,   13,   21,   29 ),
                                     simd4f_create( 7,   15,   23,   31 ));

        simd4f b = simd4f_create( 26,  -28,   30,  -32 );
        
        simd4f x;
        simd4x4f_matrix_vector3_mul(&a, &b, &x);
        
        // TODO octave simd4f: [1,3,5,7;9,11,13,15;17,19,21,23;25,27,29,31] * [26;-28;30;1]
        
    }



    it("should have simd4x4f_matrix_mul for matrix multiply") {
        
        simd4x4f a = simd4x4f_create(simd4f_create( 1,    9,   17,   25 ),
                                     simd4f_create( 3,   11,   19,   27 ),
                                     simd4f_create( 5,   13,   21,   29 ),
                                     simd4f_create( 7,   15,   23,   31 ));

        simd4x4f b = simd4x4f_create(simd4f_create(  2 , -10,   18 , -26 ),
                                     simd4f_create( -4,   12,  -20,   28 ),
                                     simd4f_create(  6,  -14,   22,  -30 ),
                                     simd4f_create( -8,   16,  -24,   32 ));
        
        simd4x4f x;
        simd4x4f_matrix_mul(&a, &b, &x);
        
        // octave simd4x4f: [1,3,5,7;9,11,13,15;17,19,21,23;25,27,29,31] * [2,-4,6,-8;-10,12,-14,16;18,-20,22,-24;-26,28,-30,32]
        should_be_equal_simd4x4f(x, simd4x4f_create(simd4f_create(-120.000000, -248.000000, -376.000000, -504.000000), simd4f_create(128.000000, 256.000000, 384.000000, 512.000000), simd4f_create(-136.000000, -264.000000, -392.000000, -520.000000), simd4f_create(144.000000, 272.000000, 400.000000, 528.000000)), epsilon );
    }
    
    
}


describe(simd4x4f, "math on elements") {
    
    it("should have simd4x4f_add for element-wise addition") {
        
        simd4x4f a = simd4x4f_create(simd4f_create(1,  2,  3,  4 ),
                                     simd4f_create(5,  6,  7,  8 ),
                                     simd4f_create(9,  10, 11, 12 ),
                                     simd4f_create(13, 14, 15, 16 ));
        
        simd4x4f b = simd4x4f_create(simd4f_create(  2 , -10,   18 , -26 ),
                                     simd4f_create( -4,   12,  -20,   28 ),
                                     simd4f_create(  6,  -14,   22,  -30 ),
                                     simd4f_create( -8,   16,  -24,   32 ));

        simd4x4f x;
        
        simd4x4f_add(&a, &b, &x);
                                 

        // octave simd4x4f: [1,5,9,13 ; 2,6,10,14 ; 3,7,11,15 ; 4,8,12,16 ] + [2,-4,6,-8;-10,12,-14,16;18,-20,22,-24;-26,28,-30,32]
        should_be_equal_simd4x4f(x, simd4x4f_create(simd4f_create(3.000000, -8.000000, 21.000000, -22.000000), simd4f_create(1.000000, 18.000000, -13.000000, 36.000000), simd4f_create(15.000000, -4.000000, 33.000000, -18.000000), simd4f_create(5.000000, 30.000000, -9.000000, 48.000000)), epsilon );
        
    }

    it("should have simd4x4f_sub for element-wise substraction") {
        
        simd4x4f a = simd4x4f_create(simd4f_create(1,  2,  3,  4 ),
                                     simd4f_create(5,  6,  7,  8 ),
                                     simd4f_create(9,  10, 11, 12 ),
                                     simd4f_create(13, 14, 15, 16 ));
        
        simd4x4f b = simd4x4f_create(simd4f_create(  2 , -10,   18 , -26 ),
                                     simd4f_create( -4,   12,  -20,   28 ),
                                     simd4f_create(  6,  -14,   22,  -30 ),
                                     simd4f_create( -8,   16,  -24,   32 ));

        simd4x4f x;
        
        simd4x4f_sub(&a, &b, &x);
                                 

        // octave simd4x4f: [1,5,9,13 ; 2,6,10,14 ; 3,7,11,15 ; 4,8,12,16 ] - [2,-4,6,-8;-10,12,-14,16;18,-20,22,-24;-26,28,-30,32]
        should_be_equal_simd4x4f(x, simd4x4f_create(simd4f_create(-1.000000, 12.000000, -15.000000, 30.000000), simd4f_create(9.000000, -6.000000, 27.000000, -20.000000), simd4f_create(3.000000, 24.000000, -11.000000, 42.000000), simd4f_create(21.000000, -2.000000, 39.000000, -16.000000)), epsilon );
        
    }

    it("should have simd4x4f_mul for element-wise multiplication") {
        
        simd4x4f a = simd4x4f_create(simd4f_create(1,  2,  3,  4 ),
                                     simd4f_create(5,  6,  7,  8 ),
                                     simd4f_create(9,  10, 11, 12 ),
                                     simd4f_create(13, 14, 15, 16 ));
        
        simd4x4f b = simd4x4f_create(simd4f_create(  2 , -10,   18 , -26 ),
                                     simd4f_create( -4,   12,  -20,   28 ),
                                     simd4f_create(  6,  -14,   22,  -30 ),
                                     simd4f_create( -8,   16,  -24,   32 ));

        simd4x4f x;
        
        simd4x4f_mul(&a, &b, &x);
                                 

        // octave simd4x4f: [1,5,9,13 ; 2,6,10,14 ; 3,7,11,15 ; 4,8,12,16 ] .* [2,-4,6,-8;-10,12,-14,16;18,-20,22,-24;-26,28,-30,32]
        should_be_equal_simd4x4f(x, simd4x4f_create(simd4f_create(2.000000, -20.000000, 54.000000, -104.000000), simd4f_create(-20.000000, 72.000000, -140.000000, 224.000000), simd4f_create(54.000000, -140.000000, 242.000000, -360.000000), simd4f_create(-104.000000, 224.000000, -360.000000, 512.000000)), epsilon );
        
    }

    it("should have simd4x4f_div for element-wise division") {
        
        simd4x4f a = simd4x4f_create(simd4f_create(1,  2,  3,  4 ),
                                     simd4f_create(5,  6,  7,  8 ),
                                     simd4f_create(9,  10, 11, 12 ),
                                     simd4f_create(13, 14, 15, 16 ));
        
        simd4x4f b = simd4x4f_create(simd4f_create(  2 , -10,   18 , -26 ),
                                     simd4f_create( -4,   12,  -20,   28 ),
                                     simd4f_create(  6,  -14,   22,  -30 ),
                                     simd4f_create( -8,   16,  -24,   32 ));

        simd4x4f x;
        
        simd4x4f_div(&a, &b, &x);
                                 

        // octave simd4x4f: [1,5,9,13 ; 2,6,10,14 ; 3,7,11,15 ; 4,8,12,16 ] ./ [2,-4,6,-8;-10,12,-14,16;18,-20,22,-24;-26,28,-30,32]
        should_be_equal_simd4x4f(x, simd4x4f_create(simd4f_create(0.500000, -0.200000, 0.166667, -0.153846), simd4f_create(-1.250000, 0.500000, -0.350000, 0.285714), simd4f_create(1.500000, -0.714286, 0.500000, -0.400000), simd4f_create(-1.625000, 0.875000, -0.625000, 0.500000)), epsilon );
        
    }
    
    
}


describe(simd4x4f, "creating projection and view matrices") {

    it("should have simd4x4f_perspective for creating perspective projection matrix") {
        
        const float fov = 10.0f;
        const float aspect = 1.6f;
        const float znear = 2.0f;
        const float zfar = 50.0f;

        const float epsilon = 0.0001f;
        
        simd4x4f x;
        simd4x4f_perspective(&x, fov, aspect, znear, zfar);
        
        should_be_equal_simd4x4f(x, simd4x4f_create(simd4f_create(7.14378,       0,        0,       -0),
                                                    simd4f_create(      0, 11.4301,        0,       -0),
                                                    simd4f_create(      0,       0, -1.08333, -4.16667),
                                                    simd4f_create(      0,       0,       -1,       -0)), epsilon);
        
        
    }

    it("should have simd4x4f_ortho for creating orthogonal projection matrix") {
        

        simd4x4f x;
        simd4x4f_ortho(&x, -10, 20, -30, 40, -50, 60);
        
        should_be_equal_simd4x4f(x, simd4x4f_create(simd4f_create(0.0666667,         0,         -0,  -0.333333 ),
                                                    simd4f_create(        0, 0.0285714,         -0,  -0.142857 ),
                                                    simd4f_create(        0,         0, -0.0181818, -0.0909091 ),
                                                    simd4f_create(        0,         0,         -0,          1 )), epsilon);
        
        
    }
    
    it("should have simd4x4f_lookat for creating look-at matrix") {
        
        simd4f eye = simd4f_create(1,2,3,0);
        simd4f center = simd4f_create(3,4,5,0);
        simd4f up = simd4f_create(0,1,0,0);

        simd4x4f x;
        simd4x4f_lookat(&x, eye, center, up);

        const float epsilon = 0.01f;
        
        should_be_equal_simd4x4f(x,simd4x4f_create(simd4f_create(-0.707107, 0, 0.707107, -1.41421),
                                                   simd4f_create(-0.408248, 0.816497, -0.408248, 0),
                                                   simd4f_create(-0.57735, -0.57735, -0.57735, 3.4641),
                                                   simd4f_create(0, 0, 0, 1)),epsilon);

        
    }
    
    
    
}


