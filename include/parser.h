#ifndef PARSER_H
#define PARSER_H

float parser();
float parser_additive(const char **pos);
float parser_number(const char **pos);
float parser_multiplicative(const char **pos);
float parser_additive(const char **pos);

#endif