
#pragma once

#include "object.hpp"
#include "reflection/reflection.hpp"

#include <unordered_map>

namespace ivd
{

class hfield_t : public hobject_t
{
public:
    hfield_t(refl::rfield_t* field_info) : m_field(field_info) {}
    // todo: make type flag that is for making antigen for GC

    template <class T>
    T get(void* ptr) const
    {
        return m_field->get<T>(ptr);
    }

    template <class T>
    void set(void* ptr, T value) const
    {
        return m_field->set<T>(ptr, value);
    }

private:
    refl::rfield_t* m_field;
};

class hfunction_t : public hobject_t
{
public:
    hfunction_t(refl::rfunction_t* func_info) : m_func(func_info){};

    template <typename R, typename... Args>
    R invoke(void* obj, Args... args) const
    {
        return m_func->invoke<R>(obj, args...);
    }

    // implement invocation
private:
    refl::rfunction_t* m_func;
};

class hclass_t : public hobject_t
{
public:
    template <class Ps, class Fs>
    hclass_t(refl::rclass_t const* rclass, Ps const* field_map, Fs const* func_map)
        : m_class(rclass), m_fields(field_map->begin(), field_map->end()),
          m_functions(func_map->begin(), func_map->end())
    {
    }

public:
    hfunction_t const* find_func(std::string_view name) { return &m_functions.at(name); }
    hfield_t const* find_field(std::string_view name) { return &m_fields.at(name); }

private:
    refl::rclass_t const* m_class;
    std::unordered_map<std::string_view, hfunction_t> const m_functions;
    std::unordered_map<std::string_view, hfield_t> const m_fields;
};

} // namespace ivd

#define GENERATE_BODY()                                                                  \
    REFLECT_CLASS();                                                                     \
                                                                                         \
public:                                                                                  \
    template <std::size_t, class>                                                        \
    struct detail_field_reflection;                                                      \
    template <std::size_t, class>                                                        \
    struct detail_function_reflection;                                                   \
                                                                                         \
public:                                                                                  \
    this_type& operator=(this_type const&) = delete;                                     \
    this_type& operator=(this_type&&)      = delete;                                     \
                                                                                         \
public:                                                                                  \
    static ivd::hclass_t* static_class()                                                 \
    {                                                                                    \
        static auto instance =                                                           \
            ivd::hclass_t(reflected_class(), reflected_fields(), reflected_functions()); \
        return &instance;                                                                \
    }
