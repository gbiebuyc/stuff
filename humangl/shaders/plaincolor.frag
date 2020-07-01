#version 330 core
out vec4 FragColor;
in vec3 FragPos;
uniform vec3 myColor;

void main()
{
    vec3 xTangent = dFdx( FragPos );
    vec3 yTangent = dFdy( FragPos );
    vec3 faceNormal = normalize( cross( xTangent, yTangent ) );
    vec3 lightDir = normalize(vec3(1, 1, 1));
    float diffuse = max(dot(faceNormal, lightDir), 0.0);
    float ambient = 0.1f;
    FragColor = (ambient + diffuse) * vec4(myColor, 1.0);
}
