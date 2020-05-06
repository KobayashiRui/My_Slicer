#version 150 core

// TODO: Replace with a uniform block
uniform vec4 lightPosition;
uniform vec3 lightIntensity;

in vec3 position;
in vec3 normal;
in vec3 color;
in vec2 vuv;

out vec4 fragColor;

vec4 adModel( const in vec3 pos, const in vec3 n, const in vec3 col )
{
    // Calculate the vector from the light to the fragment
    vec3 s = normalize( vec3( lightPosition ) - pos );

    // Calculate the diffuse component
    float diffuse = max( dot( s, n ), 0.0 );

    // Combine the ambient and diffuse contributions
    float paddingWidth = 0.05;
    vec2 tile =  mod( vuv  *10.0 , vec2(1.0));

    float mixValueX = step(paddingWidth, tile.x);
    float mixValueY = step(paddingWidth, tile.y);

    float mixValue = min(mixValueX, mixValueY);

    return vec4( vec3(mix(0.2,1.0,mixValue)), mix(1.0,0.0,mixValue));
    //return lightIntensity * ( col + col * diffuse );
}

void main()
{
    fragColor = adModel( position, normalize( normal ), color );
    //fragColor = vec4(adModel(),0.5);
}