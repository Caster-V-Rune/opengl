/* recursive subdivision of triangle to form Sierpinski gasket */
/* number of recursive steps given on command line */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "cmath"
/* initial triangle */

GLfloat v[3][2]={{-1.0, -0.58}, {1.0, -0.58}, {0.0, 1.15}};//三角形的顶点坐标

int n;

void triangle( GLfloat *a, GLfloat *b, GLfloat *c)

/* specify one triangle */
{
    GLfloat colora[3], colorb[3], colorc[3];
    colora[0] = 1.0 - sqrtf(powf(v[0][0]-a[0],2)+powf(v[0][1]-a[1],2)) / 2.0;
    colora[1] = 1.0 - sqrtf(powf(v[1][0]-a[0],2)+powf(v[1][1]-a[1],2)) / 2.0;
    colora[2] = 1.0 - sqrtf(powf(v[2][0]-a[0],2)+powf(v[2][1]-a[1],2)) / 2.0;
    colorb[0] = 1.0 - sqrtf(powf(v[0][0]-b[0],2)+powf(v[0][1]-b[1],2)) / 2.0;
    colorb[1] = 1.0 - sqrtf(powf(v[1][0]-b[0],2)+powf(v[1][1]-b[1],2)) / 2.0;
    colorb[2] = 1.0 - sqrtf(powf(v[2][0]-b[0],2)+powf(v[2][1]-b[1],2)) / 2.0;
    colorc[0] = 1.0 - sqrtf(powf(v[0][0]-c[0],2)+powf(v[0][1]-c[1],2)) / 2.0;
    colorc[1] = 1.0 - sqrtf(powf(v[1][0]-c[0],2)+powf(v[1][1]-c[1],2)) / 2.0;
    colorc[2] = 1.0 - sqrtf(powf(v[2][0]-c[0],2)+powf(v[2][1]-c[1],2)) / 2.0;

    glColor3f(colora[0],colora[1],colora[2]);
    glVertex2fv(a);//画出三个顶点
    glColor3f(colorb[0],colorb[1],colorb[2]);
    glVertex2fv(b);

    glColor3f(colorb[0],colorb[1],colorb[2]);
    glVertex2fv(b);
    glColor3f(colorc[0],colorc[1],colorc[2]);
    glVertex2fv(c);

    glColor3f(colorc[0],colorc[1],colorc[2]);
    glVertex2fv(c);
    glColor3f(colora[0],colora[1],colora[2]);
    glVertex2fv(a);
}

void divide_triangle(GLfloat *a, GLfloat *b, GLfloat *c, int m)
{

/* triangle subdivision using vertex numbers */

    GLfloat v0[2], v1[2], v2[2];
    int j;
    if(m>0)
    {
        for(j=0; j<2; j++) v0[j]=(a[j]+b[j])/2;//取各边中点
        for(j=0; j<2; j++) v1[j]=(a[j]+c[j])/2;
        for(j=0; j<2; j++) v2[j]=(b[j]+c[j])/2;
        divide_triangle(a, v0, v1, m-1);//递归划分三角形
        divide_triangle(c, v1, v2, m-1);
        divide_triangle(b, v2, v0, m-1);
    }
    else triangle(a,b,c); /* draw triangle at end of recursion *///递归结束条件,画三角形
}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT);//清除颜色缓冲
    glEnable(GL_LINE_SMOOTH);
    glLineWidth(3.0);
    glBegin(GL_LINES);//图元类型为线
    divide_triangle(v[0], v[1], v[2], n);//切分并绘图
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



