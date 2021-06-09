
// Interface class
class Serializable
{
public:
    virtual size_t serialize_size() const = 0;
    virtual void serialize(char* dataOut) const = 0;
    virtual void deserialize(const char* dataIn) = 0;
};

///

class SerialDeserial : public Serializable
{
public:
    virtual size_t serialize_size() const;
    virtual void serialize(char* dataOut) const;
    virtual void deserialize(const char* dataIn);

private:
    char* m_name;
    int   m_age;
    float m_weight;

    Serializable& s;
    void m_reserve_memory(char*& data, size_t& data_len);
};

///

template <typename POD>
class SerializablePOD
{
public:
      static size_t serialize_size(POD str);
      static char* serialize(char* target, POD value);
      static const char* deserialize(const char* source, POD& target);

};

template<>
size_t SerializablePOD<char*>::serialize_size(char* str);

template<>
const char* SerializablePOD<char*>::deserialize(const char* source, char*& target);
