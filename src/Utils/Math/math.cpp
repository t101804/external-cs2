#include "../../Utils/Header.h"





int ExtractNumber(std::string str) {
    int result = 0;

    for (char ch : str) {

        if (std::isdigit(ch)) {
            result = result * 10 + (ch - '0');
        }
    }

    return result;
}


//float DistTo(const Vector3D& vOther) const
//{
//    Vector3D delta;
//
//    delta.x = x - vOther.x;
//    delta.y = y - vOther.y;
//    delta.z = z - vOther.z;
//
//    return delta.Length();
//}

float DistTo(Vector2 value1, Vector2 value2) {
    Vector2 delta;
    delta.x = value1.x - value2.x;
    delta.y = value1.y - value2.y;
    //delta.z = value1.z - value2.z;
    return delta.Length();
}


float GetDistance(Vector3 value1, Vector3 value2)
{
    float num = value1.x - value2.x;
    float num2 = value1.y - value2.y;
    float num3 = value1.z - value2.z;

    return sqrt(num * num + num2 * num2 + num3 * num3);
}

float GetSpeed(Vector3 value)
{
    return sqrt(value.x * value.x + value.y * value.y + value.z * value.z) * 3.6f;
}

bool Vec3_Empty(const Vector3& value)
{
    return value == Vector3(0.f, 0.f, 0.f);
}

Vector3 Vec3_Transform(Vector3* vIn, Matrix* mIn)
{
    Vector3 pOut{};
    pOut.x = vIn->x * mIn->_11 + vIn->y * mIn->_21 + vIn->z * mIn->_31 + 1.f * mIn->_41;
    pOut.y = vIn->x * mIn->_12 + vIn->y * mIn->_22 + vIn->z * mIn->_32 + 1.f * mIn->_42;
    pOut.z = vIn->x * mIn->_13 + vIn->y * mIn->_23 + vIn->z * mIn->_33 + 1.f * mIn->_43;

    return pOut;
};

Vector3 CalcAngle(Vector3 local_cam, Vector3 to_point)
{
    Vector3 vOut{};
    float distance = GetDistance(local_cam, to_point);

    vOut.x = (to_point.x - local_cam.x) / distance;
    vOut.y = (to_point.y - local_cam.y) / distance;
    vOut.z = (to_point.z - local_cam.z) / distance;

    return vOut;
}

bool CsWorldToScreen(view_matrix matrix, Vector3& pos, Vector2& out) {
    out.x = matrix[0][0] * pos.x + matrix[0][1] * pos.y + matrix[0][2] * pos.z + matrix[0][3];
    out.y = matrix[1][0] * pos.x + matrix[1][1] * pos.y + matrix[1][2] * pos.z + matrix[1][3];

    float w = matrix[3][0] * pos.x + matrix[3][1] * pos.y + matrix[3][2] * pos.z + matrix[3][3];

    if (w < 0.001f)
        return false;

    float inv_w = 1.f / w;
    out.x *= inv_w;
    out.y *= inv_w;

    const ImVec2 size = ImGui::GetIO().DisplaySize;

    float x = size.x * 0.5f;
    float y = size.y * 0.5f;

    x += 0.5f * out.x * size.x + 0.5f;
    y -= 0.5f * out.y * size.y + 0.5f;

    out.x = x;
    out.y = y;

    return true;
}

bool WorldToScreen(Matrix ViewMatrix, Vector3& vWorld, Vector2& vOut)
{
    Matrix v = ViewMatrix.Transpose();
    Vector4 vec = Vector4(v._21, v._22, v._23, v._24), vec_y = Vector4(v._31, v._32, v._33, v._34), vec_z = Vector4(v._41, v._42, v._43, v._44);
    Vector3 vec_out = Vector3((vec.x * vWorld.x) + (vec.y * vWorld.y) + (vec.z * vWorld.z) + vec.w,
        (vec_y.x * vWorld.x) + (vec_y.y * vWorld.y) + (vec_y.z * vWorld.z) + vec_y.w,
        (vec_z.x * vWorld.x) + (vec_z.y * vWorld.y) + (vec_z.z * vWorld.z) + vec_z.w);

    if (vec_out.z <= 0.001f)
        return false;

    vec_out.z = 1.0f / vec_out.z;
    vec_out.x *= vec_out.z;
    vec_out.y *= vec_out.z;

    const ImVec2 size = ImGui::GetIO().DisplaySize;


	vOut.x = (size.x * 0.5f * vec_out.x) + (vec_out.x + size.x * 0.5f);
	vOut.y = (size.y * 0.5f * vec_out.y) + (vec_out.y + size.y * 0.5f);

    return true;
}