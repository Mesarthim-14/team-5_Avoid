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
 72;
 -4132.84180;4940.30811;-4239.58252;,
 -4132.84180;5234.17285;-4239.58252;,
 4076.98730;5234.17285;-4239.58252;,
 4076.98730;4940.30811;-4239.58252;,
 4076.98730;5234.17285;3863.95410;,
 4076.98730;4940.30811;3863.95410;,
 -4132.84180;4940.30811;3863.95410;,
 -4132.84180;5234.17285;3863.95410;,
 -4132.84180;877.14087;-4239.58252;,
 -4132.84180;1171.00415;-4239.58252;,
 4076.98730;1171.00415;-4239.58252;,
 4076.98730;877.14087;-4239.58252;,
 4076.98730;1171.00415;3863.95410;,
 4076.98730;877.14087;3863.95410;,
 -4132.84180;877.14087;3863.95410;,
 -4132.84180;1171.00415;3863.95410;,
 4023.28809;18.15820;50.54092;,
 4023.28809;6012.45508;50.54092;,
 4023.28809;6012.45508;3748.20898;,
 4023.28809;18.15820;3748.20898;,
 85.99176;6012.45508;3748.20898;,
 85.99176;18.15820;3748.20898;,
 85.99176;6012.45508;50.54092;,
 85.99176;18.15820;50.54092;,
 4023.28809;6012.45508;50.54092;,
 4023.28809;18.15820;50.54092;,
 4023.28809;18.15820;3748.20898;,
 4023.28809;18.15820;50.54092;,
 4023.28809;6012.45508;3748.20898;,
 4023.28809;6012.45508;50.54092;,
 -129.62445;18.15820;50.54092;,
 -129.62445;6012.45508;50.54092;,
 -129.62445;6012.45508;3748.20898;,
 -129.62445;18.15820;3748.20898;,
 -4066.92090;6012.45508;3748.20898;,
 -4066.92090;18.15820;3748.20898;,
 -4066.92090;6012.45508;50.54092;,
 -4066.92090;18.15820;50.54092;,
 -129.62445;6012.45508;50.54092;,
 -129.62445;18.15820;50.54092;,
 -129.62445;18.15820;3748.20898;,
 -129.62445;18.15820;50.54092;,
 -129.62445;6012.45508;3748.20898;,
 -129.62445;6012.45508;50.54092;,
 -129.62445;18.15820;-4137.00879;,
 -129.62445;6012.45508;-4137.00879;,
 -129.62445;6012.45508;-43.39948;,
 -129.62445;18.15820;-43.39948;,
 -4066.92090;6012.45508;-43.39948;,
 -4066.92090;18.15820;-43.39948;,
 -4066.92090;6012.45508;-4137.00879;,
 -4066.92090;18.15820;-4137.00879;,
 -129.62445;6012.45508;-4137.00879;,
 -129.62445;18.15820;-4137.00879;,
 -129.62445;18.15820;-43.39948;,
 -129.62445;18.15820;-4137.00879;,
 -129.62445;6012.45508;-43.39948;,
 -129.62445;6012.45508;-4137.00879;,
 4006.94043;18.15820;-4137.00879;,
 4006.94043;6012.45508;-4137.00879;,
 4006.94043;6012.45508;-43.39948;,
 4006.94043;18.15820;-43.39948;,
 69.64215;6012.45508;-43.39948;,
 69.64215;18.15820;-43.39948;,
 69.64215;6012.45508;-4137.00879;,
 69.64215;18.15820;-4137.00879;,
 4006.94043;6012.45508;-4137.00879;,
 4006.94043;18.15820;-4137.00879;,
 4006.94043;18.15820;-43.39948;,
 4006.94043;18.15820;-4137.00879;,
 4006.94043;6012.45508;-43.39948;,
 4006.94043;6012.45508;-4137.00879;;
 
 32;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;6,7,1,0;,
 4;5,4,7,6;,
 4;8,9,10,11;,
 4;11,10,12,13;,
 4;14,15,9,8;,
 4;13,12,15,14;,
 4;16,17,18,19;,
 4;19,18,20,21;,
 4;21,20,22,23;,
 4;23,22,24,25;,
 4;26,21,23,27;,
 4;20,28,29,22;,
 4;30,31,32,33;,
 4;33,32,34,35;,
 4;35,34,36,37;,
 4;37,36,38,39;,
 4;40,35,37,41;,
 4;34,42,43,36;,
 4;44,45,46,47;,
 4;47,46,48,49;,
 4;49,48,50,51;,
 4;51,50,52,53;,
 4;54,49,51,55;,
 4;48,56,57,50;,
 4;58,59,60,61;,
 4;61,60,62,63;,
 4;63,62,64,65;,
 4;65,64,66,67;,
 4;68,63,65,69;,
 4;62,70,71,64;;
 
 MeshMaterialList {
  4;
  32;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
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
   0.640000;0.640000;0.640000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "box_tex.png";
   }
  }
  Material {
   0.640000;0.119200;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.400000;0.400000;0.400000;1.000000;;
   1.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.400000;0.400000;0.400000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  6;
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;-1.000000;0.000000;,
  0.000000;1.000000;0.000000;;
  32;
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;0,0,0,0;,
  4;3,3,3,3;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;0,0,0,0;,
  4;3,3,3,3;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;4,4,4,4;,
  4;5,5,5,5;;
 }
 MeshTextureCoords {
  72;
  0.999890;0.540550;,
  0.985340;0.524730;,
  0.982500;0.016290;,
  0.999890;0.000110;,
  0.514660;0.067610;,
  0.500110;0.051780;,
  0.500110;0.592230;,
  0.517500;0.576040;,
  0.499890;0.540550;,
  0.485340;0.524730;,
  0.482500;0.016290;,
  0.499890;0.000110;,
  0.014660;0.067610;,
  0.000110;0.051780;,
  0.000110;0.592230;,
  0.017500;0.576040;,
  0.250000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.250000;,
  0.250000;0.250000;,
  0.500000;0.500000;,
  0.250000;0.500000;,
  0.500000;0.750000;,
  0.250000;0.750000;,
  0.500000;1.000000;,
  0.250000;1.000000;,
  0.000000;0.500000;,
  0.000000;0.750000;,
  0.750000;0.500000;,
  0.750000;0.750000;,
  0.255860;0.000000;,
  0.505860;0.000000;,
  0.505860;0.250000;,
  0.255860;0.250000;,
  0.505860;0.500000;,
  0.255860;0.500000;,
  0.505860;0.750000;,
  0.255860;0.750000;,
  0.505860;1.000000;,
  0.255860;1.000000;,
  0.005860;0.500000;,
  0.005860;0.750000;,
  0.755860;0.500000;,
  0.755860;0.750000;,
  0.251950;0.000000;,
  0.501950;0.000000;,
  0.501950;0.250000;,
  0.251950;0.250000;,
  0.501950;0.500000;,
  0.251950;0.500000;,
  0.501950;0.750000;,
  0.251950;0.750000;,
  0.501950;1.000000;,
  0.251950;1.000000;,
  0.001950;0.500000;,
  0.001950;0.750000;,
  0.751950;0.500000;,
  0.751950;0.750000;,
  0.253210;0.000000;,
  0.503210;0.000000;,
  0.503210;0.250000;,
  0.253210;0.250000;,
  0.503210;0.500000;,
  0.253210;0.500000;,
  0.503210;0.750000;,
  0.253210;0.750000;,
  0.503210;1.000000;,
  0.253210;1.000000;,
  0.003210;0.500000;,
  0.003210;0.750000;,
  0.753210;0.500000;,
  0.753210;0.750000;;
 }
}