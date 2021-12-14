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
 43;
 90.48544;11742.92480;0.00000;,
 545.16400;11742.92480;0.00000;,
 406.21619;11742.92480;-324.97931;,
 90.48544;11742.92480;-454.67883;,
 -3612.60718;5273.16504;-100.52946;,
 -3612.60718;8759.13867;-100.52946;,
 -356.90674;8759.13867;-100.52946;,
 -356.90674;5273.16504;-100.52946;,
 406.21619;18.85986;324.97931;,
 406.21619;11742.92480;324.97931;,
 90.48544;11742.92480;454.67883;,
 90.48544;18.85986;454.67883;,
 -364.19263;18.85986;0.00000;,
 -364.19263;11742.92480;0.00000;,
 -225.24483;11742.92480;-324.97931;,
 -225.24483;18.85986;-324.97931;,
 -225.24483;18.85986;324.97931;,
 -225.24483;11742.92480;324.97931;,
 545.16400;18.85986;0.00000;,
 545.16400;11742.92480;0.00000;,
 -3612.60718;5273.16504;100.52946;,
 -3612.60718;8759.13867;100.52946;,
 -356.90674;5273.16504;100.52946;,
 -356.90674;8759.13867;100.52946;,
 406.21619;11742.92480;-324.97931;,
 545.16400;11742.92480;0.00000;,
 545.16400;18.85986;0.00000;,
 406.21619;18.85986;-324.97931;,
 90.48544;18.85986;-454.67883;,
 90.48544;11742.92480;-454.67883;,
 -364.19263;11742.92480;0.00000;,
 -225.24483;11742.92480;-324.97931;,
 -225.24483;11742.92480;324.97931;,
 90.48544;11742.92480;454.67883;,
 406.21619;11742.92480;324.97931;,
 356.10727;2392.43506;-100.52946;,
 356.10727;8759.13867;-100.52946;,
 3611.80737;8759.13867;-100.52946;,
 3611.80737;2392.43506;-100.52946;,
 356.10727;2392.43506;100.52946;,
 356.10727;8759.13867;100.52946;,
 3611.80737;2392.43506;100.52946;,
 3611.80737;8759.13867;100.52946;;
 
 24;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,13,12;,
 4;18,19,9,8;,
 4;20,21,5,4;,
 4;22,23,21,20;,
 4;7,6,23,22;,
 4;24,25,26,27;,
 4;28,29,24,27;,
 4;15,14,29,28;,
 4;30,0,3,31;,
 4;32,33,0,30;,
 4;33,34,1,0;,
 4;11,10,17,16;,
 4;22,20,4,7;,
 4;21,23,6,5;,
 4;35,36,37,38;,
 4;39,40,36,35;,
 4;41,42,40,39;,
 4;38,37,42,41;,
 4;41,39,35,38;,
 4;40,42,37,36;;
 
 MeshMaterialList {
  2;
  24;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.401569;0.401569;0.401569;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.640000;0.640000;0.640000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "ship_mast.png";
   }
  }
 }
 MeshNormals {
  14;
  -0.702047;0.000000;0.712131;,
  -0.702047;0.000000;-0.712131;,
  0.702047;0.000000;0.712131;,
  0.000000;1.000000;0.000000;,
  0.702047;0.000000;-0.712131;,
  1.000000;0.000000;0.000000;,
  -0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  -0.000000;0.000000;-1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;-1.000000;0.000000;;
  24;
  4;3,3,3,3;,
  4;9,9,9,9;,
  4;2,2,6,6;,
  4;7,7,1,1;,
  4;0,0,7,7;,
  4;5,5,2,2;,
  4;11,11,11,11;,
  4;10,10,10,10;,
  4;12,12,12,12;,
  4;4,5,5,4;,
  4;8,8,4,4;,
  4;1,1,8,8;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;6,6,0,0;,
  4;13,13,13,13;,
  4;3,3,3,3;,
  4;9,9,9,9;,
  4;11,11,11,11;,
  4;10,10,10,10;,
  4;12,12,12,12;,
  4;13,13,13,13;,
  4;3,3,3,3;;
 }
 MeshTextureCoords {
  43;
  0.797666;0.956976;,
  0.782554;0.992320;,
  0.761911;0.970718;,
  0.762322;0.941865;,
  0.440396;0.039722;,
  0.440396;0.363764;,
  0.149870;0.363764;,
  0.149870;0.039722;,
  0.731914;0.001155;,
  0.731920;0.992319;,
  0.703064;0.992319;,
  0.703059;0.001155;,
  0.644327;0.001155;,
  0.644327;0.992320;,
  0.614447;0.992320;,
  0.614450;0.001155;,
  0.674204;0.001155;,
  0.674207;0.992320;,
  0.761792;0.001154;,
  0.761800;0.992319;,
  0.440396;0.039722;,
  0.440396;0.363764;,
  0.149870;0.039722;,
  0.149870;0.363764;,
  0.556734;0.992319;,
  0.526854;0.992319;,
  0.526863;0.001154;,
  0.556740;0.001155;,
  0.585595;0.001155;,
  0.585590;0.992319;,
  0.812777;0.921633;,
  0.782897;0.921633;,
  0.833420;0.943235;,
  0.833009;0.972088;,
  0.812434;0.992320;,
  0.435692;0.448434;,
  0.435692;0.985997;,
  0.145167;0.985997;,
  0.145167;0.448434;,
  0.435692;0.448434;,
  0.435692;0.985997;,
  0.145167;0.448434;,
  0.145167;0.985997;;
 }
}
