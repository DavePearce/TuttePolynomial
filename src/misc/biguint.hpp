#ifndef BIGUINT_HPP
#define BIGUINT_HPP

#include <climits>

// this class provides arbitrary sized integers
typedef unsigned int bui_word;
typedef unsigned long long bui_dword;

#define BUI_WORD_WIDTH 32U
#define BUI_DWORD_WIDTH 32U
#define BUI_WORD_MAX UINT_MAX

// problem when wors size > unsigned int ?
#define BUI_UINT_SIZE (sizeof(unsigned int) / sizeof(bui_word))
#define BUI_ULONG_SIZE (sizeof(unsigned long) / sizeof(bui_word))
#define BUI_ULONGLONG_SIZE (sizeof(unsigned long long) / sizeof(bui_word))

class biguint {
private:
  bui_word *ptr;
public:
  /* =============================== */
  /* ========= CONSTRUCTORS ======== */
  /* =============================== */

  biguint(unsigned int v);
  biguint(unsigned long v);
  biguint(unsigned long long v);
  biguint(biguint const &src);
  ~biguint();

  /* =============================== */
  /* ======== ASSIGNMENT OPS ======= */
  /* =============================== */
  
  biguint const &operator=(unsigned int v);
  biguint const &operator=(unsigned long v);
  biguint const &operator=(unsigned long long v);
  biguint const &operator=(biguint const &src);

  /* =============================== */
  /* ======== COMPARISON OPS ======= */
  /* =============================== */

  bool operator==(unsigned int v);
  bool operator==(unsigned long v);
  bool operator==(unsigned long long v);
  bool operator==(biguint const &v);

  /* =============================== */
  /* ======== ARITHMETIC OPS ======= */
  /* =============================== */

  void operator+=(unsigned int w);
  void operator+=(biguint const &src);

  void operator/=(unsigned int v);

  biguint operator+(biguint const &w) const;
  biguint operator+(unsigned int w) const;


  /* =============================== */
  /* ======== CONVERSION OPS ======= */
  /* =============================== */

  unsigned int c_uint() const;
  unsigned long c_ulong() const;
  unsigned long long c_ulonglong() const;

  /* =============================== */
  /* ======== HELPER METHODS ======= */
  /* =============================== */
  
private:
  void resize(bui_word ndepth);
};

#endif
