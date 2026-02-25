#include <math/matrix4.hpp>
#include <math/vector3.hpp>
#include <cmath>

 /*
    OpenGL inteprets arrays as matrixes using column-major order;
    the array indexes are like the following example:

            Col1    Col2    Col3    Col4
    Row1      0       4       8      12
    Row2      1       5       9      13
    Row3      2       6      10      14
    Row4      3       7      11      15
 */

Lux::Math::Matrix4::Matrix4()
    : matrix{0}
{

    //identity
    matrix[0] = 1.0f;
    matrix[5] = 1.0f;
    matrix[10] = 1.0f;
    matrix[15] = 1.0f;
}

Lux::Math::Matrix4 Lux::Math::Matrix4::ortho(f32 left, f32 right, f32 bottom, f32 top, f32 far, f32 near){
    Matrix4 result;

    result.matrix[0]  = 2.0f / (right - left);
    result.matrix[5]  = 2.0f / (top - bottom);
    result.matrix[10] = -2.0f / (far - near);

    result.matrix[12] = -(right + left) / (right - left);
    result.matrix[13] = -(top + bottom) / (top - bottom);
    result.matrix[14] = -(far + near) / (far - near);

    return result;
}

Lux::Math::Matrix4& Lux::Math::Matrix4::translate(const Vector3& vec3) {
    /*
         1    0    0    x
         0    1    0    y
         0    0    1    z
         0    0    0    1
    */
    
    matrix[12] = vec3.x;
    matrix[13] = vec3.y;
    matrix[14] = vec3.z;
    
    return *this;
}

Lux::Math::Matrix4& Lux::Math::Matrix4::rotate(const Vector3& vec3){
    /*
        X-axis rotation matrix:

         1    0    0    0
         0   cos -sin   0
         0   sin  cos   0
         0    0    0    1
    */

    f32 c = cosf(vec3.x);
    f32 s = sinf(vec3.x);

    Matrix4 x;

    x.matrix[5] = c;
    x.matrix[6] = s;
    x.matrix[9] = -s;
    x.matrix[10] = c;

    /*
        Y-axis rotation matrix:

        cos   0  sin   0
         0    1   0    0
       -sin   0  cos   0
         0    0    0   1
    */

    c = cosf(vec3.y);
    s = sinf(vec3.y);

    Matrix4 y;

    y.matrix[0] = c;
    y.matrix[2] = -s;
    y.matrix[8] = s;
    y.matrix[10] = c;

    /*
        Z-axis rotation matrix:

        cos -sin   0    0
        sin  cos   0    0
         0    0    1    0
         0    0    0    1
    */

    c = cosf(vec3.z);
    s = sinf(vec3.z);

    Matrix4 z;

    z.matrix[0] = c;
    z.matrix[1] = s;
    z.matrix[4] = -s;
    z.matrix[5] = c;


    Matrix4 result = y * x * z;

    for(int i = 0; i < 16; i++){
        matrix[i] = result.matrix[i];
    }

    return *this;
}

Lux::Math::Matrix4& Lux::Math::Matrix4::scale(const Vector3& vec3){
    /*
        Scale matrix

        x*s   0    0    0
         0   y*s   0    0
         0    0   z*s   0
         0    0    0    1
    */

    matrix[0] *= vec3.x;
    matrix[5] *= vec3.y;
    matrix[10] *= vec3.z;

    return *this;
}

Lux::Math::Matrix4 Lux::Math::Matrix4::operator*(const Matrix4& other) const{
    Matrix4 result;

    for (int col = 0; col < 4; ++col) {
        for (int row = 0; row < 4; ++row) {
            result.matrix[col * 4 + row] = 
                matrix[0 * 4 + row] * other.matrix[col * 4 + 0] +
                matrix[1 * 4 + row] * other.matrix[col * 4 + 1] +
                matrix[2 * 4 + row] * other.matrix[col * 4 + 2] +
                matrix[3 * 4 + row] * other.matrix[col * 4 + 3];
        }
    }

    return result;
}

const f32* Lux::Math::Matrix4::get_data() const{
    return matrix;
}

void Lux::Math::Matrix4::reset(){
    for(f32& elm : matrix){
        elm = 0;
    }

    matrix[0] = 1;
    matrix[5] = 1;
    matrix[10] = 1;
    matrix[15] = 1;
}