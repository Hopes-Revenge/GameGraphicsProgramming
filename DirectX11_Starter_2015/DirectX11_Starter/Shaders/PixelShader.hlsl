//#define TOON

struct DirectionalLight {
	float4 AmbientColor;
	float4 DiffuseColor;
	float3 Direction;
};

Texture2D diffuseTexture : register(t0);
SamplerState samplerState : register(s0);

cbuffer extData : register(b0)
{
	float3 cameraPosition;
	DirectionalLight light1;
	DirectionalLight light2;
};

// Struct representing the data we expect to receive from earlier pipeline stages
// - Should match the output of our corresponding vertex shader
// - The name of the struct itself is unimportant
// - The variable names don't have to match other shaders (just the semantics)
// - Each variable must have a semantic, which defines its usage
struct VertexToPixel
{
	// Data type
	//  |
	//  |   Name          Semantic
	//  |    |                |
	//  v    v                v
	float4 position		: SV_POSITION;
	float3 normal		: NORMAL;
	float2 uv			: TEXCOORD;
	float3 worldPos		: POSITION;
};

float4 CalculateLight(DirectionalLight light, VertexToPixel input, inout float4 baseColor) : COLOR0
{
	float nDotL = dot(input.normal, normalize(-light.Direction));
	//Comment out next line to get rid of toon shading
#ifdef TOON
	nDotL = smoothstep(0, 0.03f, nDotL);
#endif
	baseColor += light.AmbientColor;
	return (light.DiffuseColor * saturate(nDotL));
}

float4 CalculateRimLighting(float3 dirToCamera, VertexToPixel input) : COLOR0
{
	//FREN
	float bias = 0.56;
	float scale = 0.17f;
	float power = 3;
	float r = 1 - saturate(bias + scale * pow(1 + dot(dirToCamera, input.normal), power));
	return r.xxxx;
}

float4 CalculateSpecular(float3 dirToCamera, float3 reflection) : COLOR0
{
	float3 spec = pow(max(dot(reflection, dirToCamera), 0), 128);
#ifdef TOON
	spec = smoothstep(0, 0.03f, spec);
#endif
	return spec.xxxx;
}

// --------------------------------------------------------
// The entry point (main method) for our pixel shader
// 
// - Input is the data coming down the pipeline (defined by the struct)
// - Output is a single color (float4)
// - Has a special semantic (SV_TARGET), which means 
//    "put the output of this into the current render target"
// - Named "main" because that's the default the shader compiler looks for
// --------------------------------------------------------
float4 main(VertexToPixel input) : SV_TARGET
{
	input.normal = normalize(input.normal);
	
	float3 dirToCamera = normalize(cameraPosition - input.worldPos);
	//Specular
	float3 refl = reflect(-dirToCamera, input.normal);
	float4 baseColor = diffuseTexture.Sample(samplerState, input.uv);

	float4 lights = CalculateLight(light1, input, baseColor);
	lights += CalculateLight(light2, input, baseColor);

	return (baseColor + CalculateRimLighting(dirToCamera, input)) * lights + CalculateSpecular(dirToCamera, refl);
}