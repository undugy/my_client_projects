#version 330

uniform vec3 viewPos;        //ī�޶��� EYE
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 ambient;

uniform sampler2D outTexture;

uniform int flag;

in vec3 ex_Color;
in vec3 FragPos;
in vec3 Normal;
in vec2 uv;


out vec4 gl_FragColor;

void main()
{
    vec3 ambientLight = vec3(0.3f,0.3f,0.3f); //--- �ֺ� ���� ����
    vec3 ambient = ambientLight * lightColor; //--- �ֺ� ���� ��
    vec3 normalVector = normalize (Normal);
    vec3 lightDir = normalize(lightPos - FragPos); //--- ǥ��� ������ ��ġ�� ������ ������ �����Ѵ�.
    float diffuseLight = max(dot(normalVector, lightDir), 0.0); //--- N�� L�� ���� ������ ���� ����: ���� ����
    vec3 diffuse = diffuseLight * lightColor; //--- ��� �ݻ� ����: ����ݻ簪 * �������
    int shininess = 2280; //--- ���� ���
    vec3 viewDir = normalize (viewPos-FragPos); //--- �������� ����
    vec3 reflectDir = reflect (-lightDir, normalVector); //--- �ݻ� ����: reflect �Լ� - �Ի� ������ �ݻ� ���� ���
    float tmp =  max (dot (viewDir, reflectDir), 0.0);
    float specularLight = tmp;//--- V�� R�� ���������� ���� ����: ���� ����
    specularLight = pow(specularLight, shininess); //--- shininess ���� ���־� ���̶���Ʈ�� ������ش�.
    vec3 specular = specularLight *  lightColor; //--- �ſ� �ݻ� ����: �ſ�ݻ簪 * �������
    vec3 result = (ambient + diffuse + specular); //* ex_Color; //--- ���� ���� ������ �ȼ� ����: (�ֺ�+����ݻ�+�ſ�ݻ�����)*��ü ����

    gl_FragColor = vec4(result,1.0);
    //gl_FragColor = vec4(ex_Color,1.0);
	gl_FragColor = texture(outTexture,uv)*gl_FragColor;   //* gl_FragColor;
    if(flag == 1 ) gl_FragColor  = vec4(result,1.0)*vec4(ex_Color,1.0); //���� �ִ� ���
}