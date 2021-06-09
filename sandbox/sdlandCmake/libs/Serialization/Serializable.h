
// Interface class
class Serializable
{
public:
    Serializable() = default;
    ~Serializable() = default;
    virtual size_t serialize_size() const = 0;
    virtual void serialize(char* dataOut) const = 0;
    virtual void deserialize(const char* dataIn) = 0;
    void m_reserve_memory(char*& data, size_t& data_len)
    {
        data_len = serialize_size();
        data = new char[data_len];
    }
};

///

class Person : public Serializable
{
public:
    Person();
    Person(char* name, int age, float weight);
    ~Person() = default;
    virtual size_t serialize_size() const;
    virtual void serialize(char* dataOut) const;
    virtual void deserialize(const char* dataIn);

private:
    char* m_name;
    int   m_age;
    float m_weight;
};

///

template <typename POD>
class SerializablePOD
{
public:
      //static constexpr size_t buffersize{ 512 };

      static size_t serialize_size(POD str);

      static char* serialize(char* target, POD value);

      static const char* deserialize(const char* source, POD& target);
};

template<>
size_t SerializablePOD<char*>::serialize_size(char* str);

template<>
const char* SerializablePOD<char*>::deserialize(const char* source, char*& target);

//

template<>
size_t SerializablePOD<std::string>::serialize_size(std::string str);

template<>
char* SerializablePOD<std::string>::serialize(char* target, std::string value);

template<>
const char* SerializablePOD<std::string>::deserialize(const char* source, std::string& target);

