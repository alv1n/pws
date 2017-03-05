#ifndef STRING_H
#define STRING_H

extern int StringCompare2(const char *s1, const char *s2);

#define StringCompare(s1,s2) StringCompare2((s1), (s2))

extern int StringLength(const char *s);

#endif
