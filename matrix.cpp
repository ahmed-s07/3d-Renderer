struct vec3 {
public:    
    int x;
    int y;
    int z;

    vec3 add(vec3 other) {
        vec3 res;
        res.x = x + other.x;
        res.y = y + other.y;
        res.z = z + other.z;
    }
};

