#include <curses.h>

void red_disp(void)
{
  /* ���դ��˴ؤ������� */
  initscr(); 
  
  /* ����define��� */
  start_color();
  init_pair(1,COLOR_BLACK,COLOR_RED);
  
  clear();             //�����꡼��򥯥ꥢ������ե�å���
  bkgd(COLOR_PAIR(1)); //�����꡼�󥫥顼�ѹ�
  curs_set(0);         //����������ɽ��(1)��ɽ��
  getch();             //�ܥ��������Ԥ�

}
