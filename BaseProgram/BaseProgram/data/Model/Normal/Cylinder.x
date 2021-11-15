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
 84;
 305.46399;99.25127;445.00000;,
 305.46399;99.25127;-445.00000;,
 259.84308;188.78690;-445.00000;,
 259.84308;188.78690;445.00000;,
 188.78690;259.84305;-445.00000;,
 188.78690;259.84305;445.00000;,
 99.25131;305.46396;-445.00000;,
 99.25131;305.46396;445.00000;,
 0.00000;321.18338;-445.00000;,
 0.00000;321.18338;445.00000;,
 -99.25131;305.46396;-445.00000;,
 -99.25131;305.46396;445.00000;,
 -188.78690;259.84305;-445.00000;,
 -188.78690;259.84305;445.00000;,
 -259.84308;188.78690;-445.00000;,
 -259.84308;188.78690;445.00000;,
 -305.46399;99.25127;-445.00000;,
 -305.46399;99.25127;445.00000;,
 -321.18359;0.00000;-445.00000;,
 -321.18359;0.00000;445.00000;,
 -305.46399;-99.25127;-445.00000;,
 -305.46399;-99.25127;445.00000;,
 -259.84308;-188.78690;-445.00000;,
 -259.84308;-188.78690;445.00000;,
 -188.78690;-259.84305;-445.00000;,
 -188.78690;-259.84305;445.00000;,
 -99.25131;-305.46396;-445.00000;,
 -99.25131;-305.46396;445.00000;,
 0.00000;-321.18338;-445.00000;,
 0.00000;-321.18338;445.00000;,
 99.25131;-305.46396;-445.00000;,
 99.25131;-305.46396;445.00000;,
 188.78690;-259.84305;-445.00000;,
 188.78690;-259.84305;445.00000;,
 259.84308;-188.78690;-445.00000;,
 259.84308;-188.78690;445.00000;,
 305.46399;-99.25127;-445.00000;,
 305.46399;-99.25127;445.00000;,
 321.18359;0.00000;-445.00000;,
 321.18359;0.00000;445.00000;,
 305.46399;99.25127;-445.00000;,
 305.46399;99.25127;445.00000;,
 259.84308;188.78690;445.00000;,
 0.00000;0.00000;445.00000;,
 305.46399;99.25127;445.00000;,
 188.78690;259.84305;445.00000;,
 99.25131;305.46396;445.00000;,
 0.00000;321.18338;445.00000;,
 -99.25131;305.46396;445.00000;,
 -188.78690;259.84305;445.00000;,
 -259.84308;188.78690;445.00000;,
 -305.46399;99.25127;445.00000;,
 -321.18359;0.00000;445.00000;,
 -305.46399;-99.25127;445.00000;,
 -259.84308;-188.78690;445.00000;,
 -188.78690;-259.84305;445.00000;,
 -99.25131;-305.46396;445.00000;,
 0.00000;-321.18338;445.00000;,
 99.25131;-305.46396;445.00000;,
 188.78690;-259.84305;445.00000;,
 259.84308;-188.78690;445.00000;,
 305.46399;-99.25127;445.00000;,
 321.18359;0.00000;445.00000;,
 305.46399;99.25127;-445.00000;,
 0.00000;0.00000;-445.00000;,
 259.84308;188.78690;-445.00000;,
 188.78690;259.84305;-445.00000;,
 99.25131;305.46396;-445.00000;,
 0.00000;321.18338;-445.00000;,
 -99.25131;305.46396;-445.00000;,
 -188.78690;259.84305;-445.00000;,
 -259.84308;188.78690;-445.00000;,
 -305.46399;99.25127;-445.00000;,
 -321.18359;0.00000;-445.00000;,
 -305.46399;-99.25127;-445.00000;,
 -259.84308;-188.78690;-445.00000;,
 -188.78690;-259.84305;-445.00000;,
 -99.25131;-305.46396;-445.00000;,
 0.00000;-321.18338;-445.00000;,
 99.25131;-305.46396;-445.00000;,
 188.78690;-259.84305;-445.00000;,
 259.84308;-188.78690;-445.00000;,
 305.46399;-99.25127;-445.00000;,
 321.18359;0.00000;-445.00000;;
 
 60;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;7,6,8,9;,
 4;9,8,10,11;,
 4;11,10,12,13;,
 4;13,12,14,15;,
 4;15,14,16,17;,
 4;17,16,18,19;,
 4;19,18,20,21;,
 4;21,20,22,23;,
 4;23,22,24,25;,
 4;25,24,26,27;,
 4;27,26,28,29;,
 4;29,28,30,31;,
 4;31,30,32,33;,
 4;33,32,34,35;,
 4;35,34,36,37;,
 4;37,36,38,39;,
 4;39,38,40,41;,
 3;42,43,44;,
 3;45,43,42;,
 3;46,43,45;,
 3;47,43,46;,
 3;48,43,47;,
 3;49,43,48;,
 3;50,43,49;,
 3;51,43,50;,
 3;52,43,51;,
 3;53,43,52;,
 3;54,43,53;,
 3;55,43,54;,
 3;56,43,55;,
 3;57,43,56;,
 3;58,43,57;,
 3;59,43,58;,
 3;60,43,59;,
 3;61,43,60;,
 3;62,43,61;,
 3;44,43,62;,
 3;63,64,65;,
 3;65,64,66;,
 3;66,64,67;,
 3;67,64,68;,
 3;68,64,69;,
 3;69,64,70;,
 3;70,64,71;,
 3;71,64,72;,
 3;72,64,73;,
 3;73,64,74;,
 3;74,64,75;,
 3;75,64,76;,
 3;76,64,77;,
 3;77,64,78;,
 3;78,64,79;,
 3;79,64,80;,
 3;80,64,81;,
 3;81,64,82;,
 3;82,64,83;,
 3;83,64,63;;
 
 MeshMaterialList {
  1;
  60;
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
  0,
  0,
  0;;
  Material {
   0.483137;0.200784;0.059608;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  22;
  0.951057;0.309017;0.000000;,
  0.809016;0.587786;0.000000;,
  0.587786;0.809016;0.000000;,
  0.309016;0.951057;0.000000;,
  0.000000;1.000000;0.000000;,
  -0.309016;0.951057;0.000000;,
  -0.587786;0.809016;0.000000;,
  -0.809016;0.587786;0.000000;,
  -0.951057;0.309017;0.000000;,
  -1.000000;0.000000;0.000000;,
  -0.951057;-0.309017;0.000000;,
  -0.809016;-0.587786;0.000000;,
  -0.587786;-0.809016;0.000000;,
  -0.309016;-0.951057;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.309016;-0.951057;-0.000000;,
  0.587786;-0.809016;-0.000000;,
  0.809016;-0.587786;-0.000000;,
  0.951057;-0.309017;-0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;-1.000000;;
  60;
  4;0,0,1,1;,
  4;1,1,2,2;,
  4;2,2,3,3;,
  4;3,3,4,4;,
  4;4,4,5,5;,
  4;5,5,6,6;,
  4;6,6,7,7;,
  4;7,7,8,8;,
  4;8,8,9,9;,
  4;9,9,10,10;,
  4;10,10,11,11;,
  4;11,11,12,12;,
  4;12,12,13,13;,
  4;13,13,14,14;,
  4;14,14,15,15;,
  4;15,15,16,16;,
  4;16,16,17,17;,
  4;17,17,18,18;,
  4;18,18,19,19;,
  4;19,19,0,0;,
  3;20,20,20;,
  3;20,20,20;,
  3;20,20,20;,
  3;20,20,20;,
  3;20,20,20;,
  3;20,20,20;,
  3;20,20,20;,
  3;20,20,20;,
  3;20,20,20;,
  3;20,20,20;,
  3;20,20,20;,
  3;20,20,20;,
  3;20,20,20;,
  3;20,20,20;,
  3;20,20,20;,
  3;20,20,20;,
  3;20,20,20;,
  3;20,20,20;,
  3;20,20,20;,
  3;20,20,20;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;;
 }
 MeshTextureCoords {
  84;
  0.375000;0.312500;,
  0.375000;0.688440;,
  0.387500;0.688440;,
  0.387500;0.312500;,
  0.400000;0.688440;,
  0.400000;0.312500;,
  0.412500;0.688440;,
  0.412500;0.312500;,
  0.425000;0.688440;,
  0.425000;0.312500;,
  0.437500;0.688440;,
  0.437500;0.312500;,
  0.450000;0.688440;,
  0.450000;0.312500;,
  0.462500;0.688440;,
  0.462500;0.312500;,
  0.475000;0.688440;,
  0.475000;0.312500;,
  0.487500;0.688440;,
  0.487500;0.312500;,
  0.500000;0.688440;,
  0.500000;0.312500;,
  0.512500;0.688440;,
  0.512500;0.312500;,
  0.525000;0.688440;,
  0.525000;0.312500;,
  0.537500;0.688440;,
  0.537500;0.312500;,
  0.550000;0.688440;,
  0.550000;0.312500;,
  0.562500;0.688440;,
  0.562500;0.312500;,
  0.575000;0.688440;,
  0.575000;0.312500;,
  0.587500;0.688440;,
  0.587500;0.312500;,
  0.600000;0.688440;,
  0.600000;0.312500;,
  0.612500;0.688440;,
  0.612500;0.312500;,
  0.625000;0.688440;,
  0.625000;0.312500;,
  0.626409;0.064408;,
  0.500000;0.150000;,
  0.648603;0.107966;,
  0.591842;0.029841;,
  0.548284;0.007647;,
  0.500000;-0.000000;,
  0.451716;0.007647;,
  0.408159;0.029841;,
  0.373591;0.064409;,
  0.351397;0.107966;,
  0.343750;0.156250;,
  0.351397;0.204534;,
  0.373591;0.248091;,
  0.408159;0.282659;,
  0.451716;0.304853;,
  0.500000;0.312500;,
  0.548284;0.304853;,
  0.591841;0.282659;,
  0.626409;0.248091;,
  0.648603;0.204534;,
  0.656250;0.156250;,
  0.648603;0.892034;,
  0.500000;0.837500;,
  0.626409;0.935591;,
  0.591841;0.970159;,
  0.548284;0.992353;,
  0.500000;1.000000;,
  0.451716;0.992353;,
  0.408159;0.970159;,
  0.373591;0.935591;,
  0.351397;0.892034;,
  0.343750;0.843750;,
  0.351397;0.795466;,
  0.373591;0.751909;,
  0.408159;0.717341;,
  0.451716;0.695147;,
  0.500000;0.687500;,
  0.548284;0.695147;,
  0.591842;0.717341;,
  0.626409;0.751908;,
  0.648603;0.795466;,
  0.656250;0.843750;;
 }
}
