xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 14;
 -1422.78491;-306.59900;-771.94391;,
 -1089.08997;48.01013;-1112.62292;,
 1054.08264;48.01013;986.61987;,
 720.38586;-306.59900;1327.29651;,
 -4164.36719;1009.96606;2027.01184;,
 -2021.19641;1009.96606;4126.25098;,
 -4498.06250;655.35791;2367.68799;,
 -2354.89307;655.35791;4466.92969;,
 -1422.78491;-306.59900;-771.94391;,
 720.38586;-306.59900;1327.29651;,
 -2021.19641;1009.96606;4126.25098;,
 -2354.89307;655.35791;4466.92969;,
 -4498.06250;655.35791;2367.68799;,
 -4164.36719;1009.96606;2027.01184;;
 
 6;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;3,2,10,11;,
 4;12,13,1,0;;
 
 MeshMaterialList {
  1;
  6;
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  8;
  0.147207;-0.977622;-0.150287;,
  0.417546;-0.802457;-0.426284;,
  -0.147206;0.977622;0.150287;,
  -0.417545;0.802458;0.426283;,
  0.149621;0.976873;-0.152752;,
  -0.149621;-0.976873;0.152752;,
  0.714390;-0.000003;0.699748;,
  -0.714390;0.000001;-0.699747;;
  6;
  4;0,1,1,0;,
  4;4,2,2,4;,
  4;2,3,3,2;,
  4;5,0,0,5;,
  4;6,6,6,6;,
  4;7,7,7,7;;
 }
 MeshTextureCoords {
  14;
  0.375000;0.000000;,
  0.375000;0.250000;,
  0.625000;0.250000;,
  0.625000;0.000000;,
  0.375000;0.500000;,
  0.625000;0.500000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.375000;1.000000;,
  0.625000;1.000000;,
  0.875000;0.250000;,
  0.875000;0.000000;,
  0.125000;0.000000;,
  0.125000;0.250000;;
 }
}
