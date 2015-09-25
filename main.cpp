/* recursive subdivision of triangle to form Sierpinski gasket */
/* number of recursive steps given on command line */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cmath>
/* initial triangle */

GLfloat v[3][2]={{-1.0, -0.58}, {1.0, -0.58}, {0.0, 1.15}};//三角形的顶点坐标

int n;

void line( GLfloat *a, GLfloat *b)
{
    glVertex2fv(a);
    glVertex2fv(b);
}

void divide_line(GLfloat *a, GLfloat *b, int m)
{

/* triangle subdivision using vertex numbers */

    GLfloat vab[2], vba[2], vnew[2];
    int j;
    if(m>0)
    {
        for(j=0; j<2; j++) vab[j]=(2*a[j]+b[j])/3;
        for(j=0; j<2; j++) vba[j]=(2*b[j]+a[j])/3;
        vnew[0] = vab[0] + (vba[0]-vab[0])*0.5 + (vba[1]-vab[1])*sqrt(3)/2;
        vnew[1] = vab[1] + (vba[1]-vab[1])*0.5 - (vba[0]-vab[0])*sqrt(3)/2;
        divide_line(a,vab,m-1);
        divide_line(vab,vnew,m-1);
        divide_line(vnew,vba,m-1);
        divide_line(vba,b,m-1);

    }
    else line(a,b);
}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT);//清除颜色缓冲
    glBegin(GL_LINES);//图元类型为线
    divide_line(v[0], v[1], n);//切分并绘图
    divide_line(v[1], v[2], n);
    divide_line(v[2], v[0], n);
    glEnd();//结束
    glFlush();//刷新
}

void myinit()
{
    glMatrixMode(GL_PROJECTION);//指定投影矩阵为当前操作矩阵
    glLoadIdentity();//重置当前指定的矩阵为单位矩阵
    gluOrtho2D(-2.0, 2.0, -2.0, 2.0);//定义了一个二维图像投影矩阵
    glMatrixMode(GL_MODELVIEW);//指定模型视景矩阵为当前操作矩阵
    glClearColor (1.0, 1.0, 1.0, 1.0);//清除颜色缓冲区
    glColor3f(0.0,0.0,0.0);//指定颜色
}

void ChangeSize(GLsizei w, GLsizei h)
{
    //
    GLfloat aspectRatio;
    // 防止被0所除
    if (0 == h){
        h = 1;
    }
    // 设置视口为窗口的大小
    glViewport(0, 0, w, h);
    // 选择投影矩阵，并重置坐标系统
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // 计算窗口的纵横比（像素比）
    aspectRatio = (GLfloat) w / (GLfloat) h;
    // 定义裁剪区域（根据窗口的纵横比，并使用正投影）
    if (w <=h) {// 宽 < 高
        glOrtho(-2.0, 2.0, -2 /aspectRatio, 2 / aspectRatio, 1.0, -1.0);
    } else {// 宽 > 高
        glOrtho(-2.0 * aspectRatio, 2.0 *aspectRatio, -2.0, 2.0, 1.0, -1.0);
    }
    // 选择模型视图矩阵，并重置坐标系统
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char **argv)
{
    n=10; /* or set number of subdivision steps here *///设置递归次数
    glutInit(&argc, argv);//初始化
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//设置显示模式
    glutInitWindowSize(500, 500);//设置窗口大小
    glutCreateWindow("Sierpinski Gasket");//创建窗口
    glutDisplayFunc(display);//设置显示函数
    glutReshapeFunc(ChangeSize);
    myinit();//初始化
    glutMainLoop();//进入GLUT事件处理循环
}


