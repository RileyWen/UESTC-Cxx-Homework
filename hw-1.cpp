#include <iostream>

class cstring {
   public:
    using base_char = char;
    using const_base_char = const base_char;

    using base_char_ptr = base_char *;
    using base_char_cptr = const base_char *;

    using ref = cstring &;
    using const_ref = const cstring &;

    cstring() { this->_string_buf = nullptr; }

    ~cstring() { _clear(this->_string_buf); }

    cstring(base_char_cptr s) {
        this->_string_buf = nullptr;
        _copy(s);
    }

    cstring(const cstring &s) {
        this->_string_buf = nullptr;
        _copy(s._string_buf);
    }

    cstring(cstring &&s) {
        this->_string_buf = nullptr;
        _swap(s);
    }

    cstring(const_base_char c) {
        this->_string_buf = new base_char[2];
        this->_string_buf[0] = c;
        this->_string_buf[1] = '\0';
    }

    void clear() { _clear(this->_string_buf); }

    bool is_null() const { return _strlen(this->_string_buf) == 0; }

    size_t size() const { return _strlen(this->_string_buf); }

    ref operator=(const_ref s) {
        _copy(s._string_buf);
        return *this;
    }

    ref operator=(cstring &&s) {
        _swap(s);
        return *this;
    }

    cstring operator+(const cstring &s) {
        cstring tmp = cstring(*this);
        tmp += s;

        return tmp;
    }

    cstring operator+(const_base_char c) {
        cstring tmp = cstring(*this);
        tmp += c;

        return tmp;
    }

    ref operator+=(const_base_char c) {
        base_char_ptr old_buf = this->_string_buf;
        size_t old_len = _strlen(this->_string_buf);

        this->_string_buf = new base_char[old_len + 2];

        if (old_buf) {
            _strcpy(this->_string_buf, old_buf);
            _clear(old_buf);
        }

        this->_string_buf[old_len] = c;
        this->_string_buf[old_len + 1] = '\0';

        return *this;
    }

    ref operator+=(base_char_cptr s) {
        base_char_ptr old_buf = this->_string_buf;
        size_t old_len = _strlen(this->_string_buf);
        size_t s_len = _strlen(s);

        this->_string_buf = new base_char[old_len + s_len + 1];

        if (old_buf) {
            _strcpy(this->_string_buf, old_buf);
            _clear(old_buf);
        }
        _strcpy(this->_string_buf + old_len, s);

        return *this;
    }

    ref operator+=(const cstring &s) {
        base_char_ptr old_buf = this->_string_buf;
        size_t old_len = _strlen(this->_string_buf);
        size_t s_len = _strlen(s._string_buf);

        this->_string_buf = new base_char[old_len + s_len + 1];

        if (old_buf) {
            _strcpy(this->_string_buf, old_buf);
            _clear(old_buf);
        }
        _strcpy(this->_string_buf + old_len, s._string_buf);

        return *this;
    }

    base_char &operator[](size_t index) try {
        if (index > _strlen(this->_string_buf))
            throw std::out_of_range("Out of Range Expection!");

        return this->_string_buf[index];
    } catch (std::out_of_range &e) {
        static base_char c = '\0';
        static base_char &cref = c;

        std::cout << e.what() << std::endl;

        return cref;
    }

    base_char_cptr operator*() const { return this->_string_buf; }

    u_int operator()() const {
        u_int sum = 0;
        size_t len = _strlen(this->_string_buf);

        for (size_t i = 0; i < len; i++) {
            sum += this->_string_buf[i];
        }

        return sum;
    }

    cstring substr(size_t pos, size_t npos) {
        size_t max_len = _strlen(this->_string_buf);

        if (pos > max_len) throw std::out_of_range("pos is out of range!");
        // Include the situation when max_len == 0 || this->_string_buf ==
        // nullptr
        if (pos == max_len) return cstring();

        // n_pos is the maximum offset
        npos = std::min(max_len, pos + npos);

        cstring str = cstring();
        for (; pos < npos; pos++) str += this->_string_buf[pos];

        return str;
    }

    friend std::ostream &operator<<(std::ostream &, const cstring &);

   private:
    char *_string_buf;

    void _clear(base_char_ptr &_buf) {
        if (_buf) delete[] _buf;

        _buf = nullptr;
    }

    void _swap(ref s) { std::swap(this->_string_buf, s._string_buf); }

    void _copy(base_char_cptr s) {
        _clear(this->_string_buf);

        this->_string_buf = new base_char[_strlen(s) + 1];
        _strcpy(this->_string_buf, s);
    }

    void _strcpy(base_char_ptr dst, base_char_cptr src) {
        while ((*dst++ = *src++))
            ;
    }

    size_t _strlen(base_char_cptr s) const {
        if (!s) return 0;

        base_char_cptr p = const_cast<base_char_cptr>(s);
        while (*p) ++p;
        return p - s;
    }
};

std::ostream &operator<<(std::ostream &os, const cstring &s) {
    if (s._string_buf) os << s._string_buf;
    // else std::cout<<"Empty string!\n";

    return os;
}

int main() {
    // test
    char buf[1024];
    std::cin >> buf;
    cstring s1(buf);
    std::cin >> buf;
    cstring s2(buf);

    s1[6] = 'A';

    cstring s3 = 'B';
    s3 = (s1 + s2).substr(7, s2.size());
    std::cout << s1 << *s3 << ' ' << s3();
    return 0;
}