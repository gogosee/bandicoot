#include <stdio.h>
 
// ��Ա
class Player
{
public:
       Player(char* _name) : name(_name){}
      
       virtual void Attack()=0;
       virtual void Defense()=0;
 
       char* name;
};
 
// ǰ��
class Forwards : public Player
{
public:
       Forwards(char* name) : Player(name){}
      
       virtual void Attack()
       {
              printf("ǰ�� %s ����\n", name);
       }
      
       virtual void Defense()
       {
              printf("ǰ�� %s ����\n", name);
       }
};
 
// �з�
class Center : public Player
{
public:
       Center(char* name) : Player(name){}
      
       virtual void Attack()
       {
              printf("�з� %s ����\n", name);
       }
      
       virtual void Defense()
       {
              printf("�з� %s ����\n", name);
       }
};
 
// ����
class Guards : public Player
{
public:
       Guards(char* name) : Player(name){}
      
       virtual void Attack()
       {
              printf("���� %s ����\n", name);
       }
      
       virtual void Defense()
       {
              printf("���� %s ����\n", name);
       }
};
 
// �⼮�з�
class ForeignCenter
{
public:
       void Attack()
       {
              printf("�⼮�з� %s ����\n", name);
       }
      
       void Defense()
       {
              printf("�⼮�з� %s ����\n", name);
       }
      
       char* name;
};
 
// ������
class Translator : public Player
//class Translator 
{
public:
       Translator(char* name) : Player(name)
       //Translator(char* name) 
       {
              wjzf.name = name;
       }
      
       virtual void Attack()
       {
              wjzf.Attack();
       }
      
       virtual void Defense()
       {
              wjzf.Defense();
       }
protected:
       ForeignCenter wjzf;
};
 
int main()
{
       Player* b = new Forwards("�͵ٶ�");
       b->Attack();
      
       Player* m = new Guards("��˸��׵�");
       m->Attack();
      
       Player* ym = new Translator("Ҧ��");
       //Translator* ym = new Translator("Ҧ��");
       ym->Attack();
       ym->Defense();
      
       delete b;
       delete m;
       delete ym;
      
       return 0;
}


