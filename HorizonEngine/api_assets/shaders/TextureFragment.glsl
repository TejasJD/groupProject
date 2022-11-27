# version 420 core
layout (location = 0) out vec4 f_Color1;
layout (location = 1) out int f_EntityId;

in vec4 v_Color;
in vec2 v_TexCoord;
in float v_TexSlot;
in float v_TilingFactor;
in flat int v_EntityId;

uniform sampler2D u_Textures[32];

void main()
{
	f_Color1 = texture(u_Textures[int(v_TexSlot)], v_TexCoord * v_TilingFactor) * v_Color;
	f_EntityId = v_EntityId;
}