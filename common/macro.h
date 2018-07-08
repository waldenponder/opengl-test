#ifdef EXPORT_COMMON
#define COMMON_API _declspec(dllexport)
#else 
#define COMMON_API _declspec(dllimport)
#endif


#define   TVec3       glm::vec3
#define   TVec4       glm::vec4
#define   TQuat       glm::vec4
#define   TVector     std::vector
#define   TMat4		  glm::mat4
#define   TMat3		  glm::mat3
#define   X_AXIS      TVec3(1, 0, 0)
#define   Y_AXIS      TVec3(0, 1, 0)
#define   Z_AXIS      TVec3(0, 0, 1)
#define   CLEAR_COLOR 0.1, 0.5, 0.8, 1
#define   PI          3.1415926
#define   FLOAT_SIZE  (sizeof(GLfloat))

#define PREPARE_GLFW_WINDOW(nW, nH, strName, key_callback)\
	glfwInit();\
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);\
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);\
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);\
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);\
	window = glfwCreateWindow(nW, nH, strName, nullptr, nullptr); \
	glfwMakeContextCurrent(window); \
	glewInit(); \
	int w, h; \
	glfwGetFramebufferSize(window, &w, &h); \
	glViewport(0, 0, w, h);\
    if(key_callback) glfwSetKeyCallback(window, key_callback);

#define   WINDOW_WIDTH   1024
#define   WINDOW_HEIGHT  1024
#define   WINDOW_NAME    "learn gl"

#define   OUT
#define   IN
#define   OPTIONAL

#define   ToVec4(v3)  TVec4((v3)[0], (v3)[1], (v3)[2], 0)
#define   ToVec3(v4)  TVec3((v4)[0], (v4)[1], (v4)[2]) 

#define   FRAME_RATE_BEGIN  long t_frame_rate_begin = clock();
#define   FRAME_RATE_END    std::cout << "fps : " << std::setprecision(3) << 1000.0 / float(clock() - t_frame_rate_begin)<< std::endl;


#define GLUS_MAX_VERTICES 65536
#define GLUS_VERTICES_FACTOR 4
#define GLUS_VERTICES_DIVISOR 4

#define GLUS_MAX_STRING 	256

#define GLUS_MAX_FILENAME	2048
#define GLUS_MAX_INDICES  (GLUS_MAX_VERTICES*GLUS_VERTICES_FACTOR)
