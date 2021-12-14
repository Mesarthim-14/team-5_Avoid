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
 24;
 9.16000;304.41748;-4000.00000;,
 2000.00000;304.41748;-3403.92969;,
 2000.00000;-295.58252;-3403.92969;,
 9.16000;-295.58252;-4000.00000;,
 9.16000;304.41748;-2000.00000;,
 2000.00000;304.41748;-1403.93005;,
 9.16000;-295.58252;-2000.00000;,
 2000.00000;-295.58252;-1403.93005;,
 -2000.00000;-295.58252;-1403.93005;,
 -2000.00000;304.41748;-1403.93005;,
 -2000.00000;304.41748;-3403.92969;,
 -2000.00000;-295.58252;-3403.92969;,
 9.16000;-295.58252;3596.07031;,
 2000.00000;-295.58252;3000.00000;,
 2000.00000;304.41748;3000.00000;,
 9.16000;304.41748;3596.07031;,
 9.16000;-295.58252;1596.06995;,
 2000.00000;-295.58252;1000.00000;,
 9.16000;304.41748;1596.06995;,
 2000.00000;304.41748;1000.00000;,
 -2000.00000;304.41748;1000.00000;,
 -2000.00000;-295.58252;1000.00000;,
 -2000.00000;-295.58252;3000.00000;,
 -2000.00000;304.41748;3000.00000;;
 
 20;
 4;0,1,2,3;,
 4;4,5,1,0;,
 4;6,7,5,4;,
 4;3,2,7,6;,
 4;2,1,5,7;,
 4;8,9,10,11;,
 4;8,11,3,6;,
 4;9,8,6,4;,
 4;10,9,4,0;,
 4;11,10,0,3;,
 4;12,13,14,15;,
 4;16,17,13,12;,
 4;18,19,17,16;,
 4;15,14,19,18;,
 4;14,13,17,19;,
 4;20,21,22,23;,
 4;20,23,15,18;,
 4;21,20,18,16;,
 4;22,21,16,12;,
 4;23,22,12,15;;
 
 MeshMaterialList {
  1;
  20;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
   0.401569;0.401569;0.401569;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "kaiten_mokume.png";
   }
  }
 }
 MeshNormals {
  16;
  -1.000000;0.000000;0.000000;,
  0.286826;0.000000;-0.957983;,
  0.000000;1.000000;0.000000;,
  -0.286826;0.000000;0.957983;,
  0.001254;0.000000;-0.999999;,
  -0.001254;0.000000;0.999999;,
  0.286826;0.000000;0.957983;,
  0.000000;-1.000000;-0.000000;,
  -0.286826;0.000000;-0.957983;,
  0.001254;0.000000;0.999999;,
  -0.001254;0.000000;-0.999999;,
  1.000000;0.000000;0.000000;,
  0.284423;0.000000;0.958699;,
  -0.284423;0.000000;-0.958699;,
  0.284423;0.000000;-0.958699;,
  -0.284423;0.000000;0.958699;;
  20;
  4;4,1,1,4;,
  4;2,2,2,2;,
  4;5,3,3,5;,
  4;7,7,7,7;,
  4;11,11,11,11;,
  4;0,0,0,0;,
  4;7,7,7,7;,
  4;12,12,5,5;,
  4;2,2,2,2;,
  4;13,13,4,4;,
  4;9,6,6,9;,
  4;7,7,7,7;,
  4;10,8,8,10;,
  4;2,2,2,2;,
  4;11,11,11,11;,
  4;0,0,0,0;,
  4;2,2,2,2;,
  4;14,14,10,10;,
  4;7,7,7,7;,
  4;15,15,9,9;;
 }
 MeshTextureCoords {
  24;
  0.025176;0.498787;,
  0.095933;0.235055;,
  0.095933;0.235055;,
  0.025176;0.498787;,
  0.262588;0.498787;,
  0.333345;0.235055;,
  0.262588;0.498787;,
  0.333345;0.235055;,
  0.333345;0.764945;,
  0.333345;0.764945;,
  0.095933;0.764945;,
  0.095933;0.764945;,
  0.926875;0.498787;,
  0.856118;0.235055;,
  0.856118;0.235055;,
  0.926875;0.498787;,
  0.689463;0.498787;,
  0.618706;0.235055;,
  0.689463;0.498787;,
  0.618706;0.235055;,
  0.618706;0.764945;,
  0.618706;0.764945;,
  0.856118;0.764945;,
  0.856118;0.764945;;
 }
}
