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
 26;
 4308.16260;6257.37598;15969.26660;,
 4308.16211;6257.37598;-15969.26660;,
 -4307.85400;6257.37598;-15969.26660;,
 -4307.85352;6257.37598;15969.26660;,
 -4307.85352;4466.38184;15969.26660;,
 -4307.85352;6257.37598;15969.26660;,
 -4307.85400;6257.37598;-15969.26660;,
 -4307.85400;4466.38184;-15969.26660;,
 -4307.85400;4466.38184;-15969.26660;,
 4308.16211;4466.38184;-15969.26660;,
 4308.16260;4466.38184;15969.26660;,
 4308.16260;6257.37598;15969.26660;,
 -4307.85352;6257.37598;15969.26660;,
 -4307.85352;4466.38184;15969.26660;,
 4308.16211;4466.38184;-15969.26660;,
 4308.16211;6257.37598;-15969.26660;,
 4308.16260;6257.37598;15969.26660;,
 4308.16260;4466.38184;15969.26660;,
 4308.16211;22.46289;-12244.88770;,
 4308.16260;22.46289;15969.26660;,
 4308.16260;22.46289;15969.26660;,
 -4307.85352;22.46289;15969.26660;,
 -4307.85400;22.46289;-12244.88770;,
 4308.16211;22.46289;-12244.88770;,
 -4307.85352;22.46289;15969.26660;,
 -4307.85400;22.46289;-12244.88770;;
 
 9;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,2,1,9;,
 4;10,11,12,13;,
 4;14,15,16,17;,
 4;18,14,17,19;,
 4;20,10,13,21;,
 4;22,8,9,23;,
 4;24,4,7,25;;
 
 MeshMaterialList {
  1;
  9;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.640000;0.640000;0.640000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "big_floor_ship_tex.png";
   }
  }
 }
 MeshNormals {
  11;
  0.000000;1.000000;0.000000;,
  1.000000;-0.000000;-0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;-0.642331;-0.766427;,
  -1.000000;0.000000;0.000000;,
  0.000000;-0.341740;-0.939795;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;-0.000000;-0.000000;,
  1.000000;0.000000;-0.000000;,
  -1.000000;0.000000;0.000000;;
  9;
  4;0,0,0,0;,
  4;4,6,6,4;,
  4;5,7,7,5;,
  4;2,2,2,2;,
  4;8,9,9,8;,
  4;1,8,8,1;,
  4;2,2,2,2;,
  4;3,5,5,3;,
  4;10,4,4,10;;
 }
 MeshTextureCoords {
  26;
  0.045390;0.500730;,
  0.604540;0.500730;,
  0.604540;0.730680;,
  0.045390;0.730680;,
  0.989690;0.924930;,
  0.989690;0.989670;,
  0.312860;0.989670;,
  0.312860;0.924930;,
  0.713040;0.730680;,
  0.713040;0.500730;,
  0.988720;0.402110;,
  0.988720;0.474370;,
  0.486710;0.474370;,
  0.486710;0.402110;,
  0.312860;0.924930;,
  0.312860;0.989670;,
  0.989690;0.989670;,
  0.989690;0.924930;,
  0.391780;0.764320;,
  0.989690;0.764320;,
  0.988720;0.222880;,
  0.486710;0.222880;,
  0.989970;0.730680;,
  0.989970;0.500730;,
  0.989690;0.764320;,
  0.391780;0.764320;;
 }
}
