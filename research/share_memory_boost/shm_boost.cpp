// reference: http://blog.csdn.net/dx2880/article/details/7315761


#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/map.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <iostream>

using namespace boost::interprocess;

//���ͺ�allocator�Ķ��壬ʹ�ù����ڴ�ʱ��Ҫʹ��boost::interprocess��
//����ʵ�ֵ�����������ʹ�ñ�׼����
typedef managed_shared_memory::segment_manager                       segment_manager_t;
typedef allocator<void, segment_manager_t>                           void_allocator;
typedef allocator<int, segment_manager_t>                            int_allocator;
typedef vector<int, int_allocator>                                   int_vector;
typedef allocator<int_vector, segment_manager_t>                     int_vector_allocator;
typedef vector<int_vector, int_vector_allocator>                     int_vector_vector;
typedef allocator<char, segment_manager_t>                           char_allocator;
typedef basic_string<char, std::char_traits<char>, char_allocator>   char_string;

class complex_data
{
  int               id_;
  char_string       char_string_;
  int_vector_vector int_vector_vector_;

public:
  //��Ϊvoid_allocator�ܹ�ת��Ϊ�κ����͵�allocator<T>, ���������ܹ��򵥵��ڹ��캯����
  //ʹ��void_allocator����ʼ�����е��ڲ�����
  complex_data(int id, const char *name, const void_allocator &void_alloc)
    : id_(id), char_string_(name, void_alloc), int_vector_vector_(void_alloc)
  {}
  ~complex_data(){}
};

//��map��key����Ϊһ��string������map��value����Ϊһ��complex_data����
typedef std::pair<const char_string, complex_data>                      map_value_type;
typedef allocator<map_value_type, segment_manager_t>                    map_value_type_allocator;
typedef map< char_string, complex_data
, std::less<char_string>, map_value_type_allocator>          complex_map_type;

int main ()
{
  //�ڳ���ʼ�ͽ�����ʱ���Ƴ�ͬ���Ĺ����ڴ�
  //���ֻ�Ƕ��������򴴽��Ĺ����ڴ���򲻸ð���remover
  struct shm_remove
  {
    shm_remove() { shared_memory_object::remove("MySharedMemory"); }
    ~shm_remove(){ shared_memory_object::remove("MySharedMemory"); }
  } remover;
  //���������ڴ棬���ݲ��ԣ���32λ��linux�ϣ����������Ĺ����ڴ��С
  //���Ϊ2^31-1������Ƕ��������򴴽��Ĺ����ڴ棬��˾�ӦдΪ
  //managed_shared_memory segment(open_only, "MySharedMemory");
  managed_shared_memory segment(create_only,"MySharedMemory", 65536);

  //һ���ܹ�ת��Ϊ�κ�allocator<T, segment_manager_t>���͵�allocator 
  void_allocator alloc_inst (segment.get_segment_manager());

  //�ڹ����ڴ��ϴ���map
  //���map�����������򴴽������߲�ȷ��map�Ƿ��Ѵ�����Ӧ���£�
  //complex_map_type *mymap = segment.find_or_construct<complex_map_type>
  complex_map_type *mymap = segment.construct<complex_map_type>
    ("MyMap")(std::less<char_string>(), alloc_inst);

  for(int i = 0; i < 100; ++i){
    //key(string) ��value(complex_data) ����Ҫ�����ǵĹ��캯����
	//����һ��allocator
	char tmp[16] = "";
	sprintf(tmp, "test%d", i);
    char_string  key_object(tmp, alloc_inst);
    complex_data mapped_object(i, "default_name", alloc_inst);
    map_value_type value(key_object, mapped_object);
    //��map�в�ֵ
    mymap->insert(value);
  }

  return 0;
}



