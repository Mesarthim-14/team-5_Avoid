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
 45;
 0.00000;0.00008;-943.35522;,
 456.60422;-456.60413;-943.35522;,
 0.00000;-645.73560;-943.35529;,
 645.73560;0.00011;-943.35522;,
 456.60422;456.60428;-943.35522;,
 -0.00006;645.73566;-943.35522;,
 -456.60425;456.60425;-943.35522;,
 -645.73560;0.00008;-943.35522;,
 -456.60422;-456.60410;-943.35522;,
 0.00000;-0.00008;943.35522;,
 0.00000;-645.73566;943.35522;,
 456.60422;-456.60428;943.35522;,
 645.73560;-0.00006;943.35522;,
 456.60422;456.60413;943.35522;,
 -0.00006;645.73560;943.35529;,
 -456.60425;456.60410;943.35522;,
 -645.73560;-0.00009;943.35522;,
 -456.60422;-456.60425;943.35522;,
 -11.96517;712.26086;-1.74890;,
 -0.00006;645.73560;943.35529;,
 456.60422;456.60413;943.35522;,
 500.14026;500.14023;-1.74893;,
 456.60422;456.60428;-943.35522;,
 -0.00006;645.73566;-943.35522;,
 -456.60425;456.60425;-943.35522;,
 -524.07037;500.14020;-1.74896;,
 -456.60425;456.60410;943.35522;,
 645.73560;-0.00006;943.35522;,
 712.26080;-11.96509;-1.74896;,
 645.73560;0.00011;-943.35522;,
 -645.73560;0.00008;-943.35522;,
 -642.52301;-0.00001;-1.74896;,
 -645.73560;-0.00009;943.35522;,
 456.60422;-456.60428;943.35522;,
 500.14023;-524.07031;-1.74896;,
 456.60422;-456.60413;-943.35522;,
 -456.60422;-456.60410;-943.35522;,
 -454.33255;-454.33252;-1.74896;,
 -456.60422;-456.60425;943.35522;,
 0.00000;-645.73566;943.35522;,
 0.00000;-642.52307;-1.74899;,
 0.00000;-645.73560;-943.35529;,
 0.00000;-645.73560;-943.35529;,
 0.00000;-642.52307;-1.74899;,
 0.00000;-645.73566;943.35522;;
 
 32;
 3;0,1,2;,
 3;0,3,1;,
 3;0,4,3;,
 3;0,5,4;,
 3;0,6,5;,
 3;0,7,6;,
 3;0,8,7;,
 3;0,2,8;,
 3;9,10,11;,
 3;9,11,12;,
 3;9,12,13;,
 3;9,13,14;,
 3;9,14,15;,
 3;9,15,16;,
 3;9,16,17;,
 3;9,17,10;,
 4;18,19,20,21;,
 4;18,21,22,23;,
 4;18,23,24,25;,
 4;18,25,26,19;,
 4;21,20,27,28;,
 4;21,28,29,22;,
 4;25,24,30,31;,
 4;25,31,32,26;,
 4;28,27,33,34;,
 4;28,34,35,29;,
 4;31,30,36,37;,
 4;31,37,38,32;,
 4;34,33,39,40;,
 4;34,40,41,35;,
 4;37,36,42,43;,
 4;37,43,44,38;;
 
 MeshMaterialList {
  2;
  32;
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
    "data\\Texture\\ModelTex\\taru_tex.png";
   }
  }
  Material {
   0.288627;0.103529;0.015686;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "mokume.png";
   }
  }
 }
 MeshNormals {
  34;
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;-1.000000;,
  -0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;-0.000000;1.000000;,
  -0.000000;-0.000000;1.000000;,
  -0.000000;-0.000000;1.000000;,
  -0.000000;-0.000000;1.000000;,
  0.000130;1.000000;-0.000130;,
  0.707107;0.707107;-0.000121;,
  -0.735065;0.677997;-0.000110;,
  1.000000;0.000130;-0.000130;,
  -0.999196;-0.040097;-0.000035;,
  0.677997;-0.735065;-0.000110;,
  -0.707107;-0.707107;0.000006;,
  -0.040097;-0.999196;-0.000035;,
  0.000130;0.997532;0.070214;,
  0.705611;0.705611;0.065008;,
  0.705600;0.705600;-0.065248;,
  0.000131;0.997514;-0.070473;,
  -0.733750;0.676782;-0.059802;,
  -0.733758;0.676793;0.059582;,
  0.997532;0.000130;0.070214;,
  0.997514;0.000131;-0.070473;,
  -0.999017;-0.040090;-0.018912;,
  -0.999018;-0.040090;0.018842;,
  0.676793;-0.733758;0.059582;,
  0.676782;-0.733750;-0.059803;,
  -0.707103;-0.707103;0.003412;,
  -0.707103;-0.707103;-0.003399;,
  -0.040090;-0.999018;0.018842;,
  -0.040090;-0.999017;-0.018912;;
  32;
  3;0,2,1;,
  3;0,3,2;,
  3;0,3,3;,
  3;0,3,3;,
  3;0,3,3;,
  3;0,3,3;,
  3;0,4,3;,
  3;0,1,4;,
  3;9,5,5;,
  3;9,5,5;,
  3;9,5,6;,
  3;9,6,7;,
  3;9,7,8;,
  3;9,8,5;,
  3;9,5,5;,
  3;9,5,5;,
  4;10,18,19,11;,
  4;10,11,20,21;,
  4;10,21,22,12;,
  4;10,12,23,18;,
  4;11,19,24,13;,
  4;11,13,25,20;,
  4;12,22,26,14;,
  4;12,14,27,23;,
  4;13,24,28,15;,
  4;13,15,29,25;,
  4;14,26,30,16;,
  4;14,16,31,27;,
  4;15,28,32,17;,
  4;15,17,33,29;,
  4;16,30,33,17;,
  4;16,17,32,31;;
 }
 MeshTextureCoords {
  45;
  0.500000;0.500000;,
  0.804420;0.804420;,
  0.500000;0.930515;,
  0.930515;0.500000;,
  0.804420;0.195580;,
  0.500000;0.069485;,
  0.195580;0.195580;,
  0.069485;0.500000;,
  0.195580;0.804420;,
  0.500000;0.500000;,
  0.500000;0.930515;,
  0.804420;0.804420;,
  0.930515;0.500000;,
  0.804420;0.195580;,
  0.500000;0.069485;,
  0.195580;0.195580;,
  0.069485;0.500000;,
  0.195580;0.804420;,
  0.502673;0.497565;,
  0.500000;1.005713;,
  0.373563;1.004824;,
  0.375012;0.496569;,
  0.376433;-0.010213;,
  0.500000;-0.009325;,
  0.623567;-0.010213;,
  0.628706;0.496569;,
  0.626437;1.004824;,
  0.247990;1.002680;,
  0.247348;0.494164;,
  0.252049;-0.012357;,
  0.747952;-0.012357;,
  0.749977;0.494221;,
  0.752010;1.002680;,
  0.123594;1.000536;,
  0.121299;0.491760;,
  0.126465;-0.014501;,
  0.873535;-0.014501;,
  0.874981;0.492087;,
  0.876406;1.000536;,
  0.000000;0.999648;,
  0.000000;0.491204;,
  0.000000;-0.015389;,
  1.000000;-0.015389;,
  1.000000;0.491204;,
  1.000000;0.999648;;
 }
}
