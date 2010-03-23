// 在此处引用程序要求的附加头文件:
#include "BasicWindow.h"
#include "Texture.h"
#include "Fluid.h"

// 在此处加入程序要求的库到链接器中:
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

// 在此处定义全局变量:
GL_Window*	OGL_window;
Keys*		OGL_keys;

// 在此处定义用户变量:
Fluid* fluid;
int timestep;

BOOL Initialize(GL_Window* window, Keys* keys)						// 初始化场景
{
	// 设置全局变量
	OGL_window	= window;
	OGL_keys	= keys;
	fluid = new Fluid();
	timestep = 1000;

	// 在此处初始化绘制场景
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);							// 清屏为黑色
	glClearDepth(1.0f);												// 设置深度缓存
	glEnable(GL_DEPTH_TEST);//glDisable(GL_DEPTH_TEST);										// 关闭深度测试
	glShadeModel(GL_SMOOTH);										// 阴暗处理采用平滑方式
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);				// 最精细的透视计算	

	return TRUE;													// 初始化成功返回TRUE
}

void DrawSceneGL(void)												// 绘制场景
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);				// 清除颜色和深度缓存
	glLoadIdentity();												// 重置当前矩阵

	// 在此处添加代码进行绘制:
	glTranslatef(-5.0f,-5.0f,-30.0f);
	fluid->render(timestep);

	glFlush();														// 刷新GL命令队列
}

void Update()														// 在此处更新对消息的动作
{
	if (OGL_keys->keyDown[VK_ESCAPE] == TRUE)						// 判断ESC键是否按下
	{
		TerminateApplication(OGL_window);							// 结束程序 	   
	}

	if (OGL_keys->keyDown[VK_F1] == TRUE)							// 判断F1是否按下
	{
		PostMessage(OGL_window->hWnd, WM_TOGGLEFULLSCREEN, 0, 0);	// 在全屏/窗口模式间切换
	}
}

void Deinitialize(void)												// 在此处做退出前扫尾工作
{

}