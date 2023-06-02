#include "Cube.hpp"

Cube::Cube()
{
    _vertexBuffer = nullptr;
    _indexBuffer = nullptr;
}

Cube::Cube(DirectX::XMFLOAT3 position)
{
    _vertexBuffer = nullptr;
    _indexBuffer = nullptr;
    transform.position = position;
}

Cube::~Cube()
{
    if (_vertexBuffer)
    {
        _vertexBuffer->Release();
        _vertexBuffer = nullptr;
    }
    if (_indexBuffer)
    {
        _indexBuffer->Release();
        _indexBuffer = nullptr;
    }
}

static constexpr VertexPositionColorUv vertices[] = {
    //Front
    {Position{ -0.5f,  -0.5f, 0.5f }, Color{ 1.0f, 0.0f, 0.0f}, Uv{ 0.0f, 1.0f }},
    {Position{  0.5f,  -0.5f, 0.5f }, Color{ 0.0f, 1.0f, 0.0f}, Uv{ 1.0f, 1.0f }},
    {Position{ -0.5f,   0.5f, 0.5f }, Color{ 0.0f, 0.0f, 1.0f}, Uv{ 0.0f, 0.0f }},
    {Position{  0.5f,   0.5f, 0.5f }, Color{ 1.0f, 1.0f, 0.0f}, Uv{ 1.0f, 0.0f }},

    //Back
    {Position{ -0.5f,  -0.5f, -0.5f }, Color{ 0.0f, 1.0f, 1.0f}, Uv{ 0.0f, 1.0f }},
    {Position{  0.5f,  -0.5f, -0.5f }, Color{ 1.0f, 0.0f, 1.0f}, Uv{ 1.0f, 1.0f }},
    {Position{ -0.5f,   0.5f, -0.5f }, Color{ 0.0f, 0.0f, 0.0f}, Uv{ 0.0f, 0.0f }},
    {Position{  0.5f,   0.5f, -0.5f }, Color{ 1.0f, 1.0f, 1.0f}, Uv{ 1.0f, 0.0f }},
};

static constexpr uint32_t indices[] = {
    //Top
    7, 6, 2,
    2, 3, 7,

    //Bottom
    0, 4, 5,
    5, 1, 0,

    //Left
    0, 2, 6,
    6, 4, 0,

    //Right
    7, 3, 1,
    1, 5, 7,

    //Front
    3, 2, 0,
    0, 1, 3,

    //Back
    4, 6, 7,
    7, 5, 4
};

bool Cube::Initialize(ID3D11Device* device)
{

    D3D11_BUFFER_DESC vertexBufferDesc;
    ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc)); // not sure if this is needed, I just created it
    vertexBufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
    vertexBufferDesc.ByteWidth = sizeof(VertexPositionColorUv) * ARRAYSIZE(vertices);
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = 0;  // Don't set D3D11_CPU_ACCESS_WRITE for a D3D11_USAGE_DEFAULT resource
    vertexBufferDesc.MiscFlags = 0;  // We don't need any flags for now https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ne-d3d11-d3d11_resource_misc_flag


    D3D11_SUBRESOURCE_DATA vertexData;
    vertexData.pSysMem = vertices;
    HRESULT hr = device->CreateBuffer(&vertexBufferDesc, &vertexData, &_vertexBuffer);
    if (FAILED(hr)) return false;

    // Create and initialize the index buffer
    D3D11_BUFFER_DESC indexBufferDesc;
    ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));
    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    indexBufferDesc.ByteWidth = sizeof(uint32_t) * ARRAYSIZE(indices);
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

    D3D11_SUBRESOURCE_DATA indexData;
    indexData.pSysMem = indices;
    hr = device->CreateBuffer(&indexBufferDesc, &indexData, &_indexBuffer);
    if (FAILED(hr)) return false;

    return true;

}

void Cube::Update()
{
 
}

void Cube::Render(ID3D11DeviceContext* deviceContext)
{
    // Set the vertex and index buffers, and draw the cube
    UINT stride = sizeof(VertexPositionColorUv);
    UINT offset = 0;
    deviceContext->IASetVertexBuffers(0, 1, &_vertexBuffer, &stride, &offset);
    deviceContext->IASetIndexBuffer(_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
    deviceContext->DrawIndexed(ARRAYSIZE(indices), 0, 0);
}