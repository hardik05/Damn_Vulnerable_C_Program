#pragma once

#ifdef DamnVulnerableDll_EXPORTS
#define DamnVulnerableDll_API __declspec(dllexport)
#else
#define DamnVulnerableDll_API __declspec(dllimport)
#endif

extern "C" DamnVulnerableDll_API void ProcessImage_init(char *filename);

// Produce the next value in the sequence.
// Returns true on success and updates current value and index;
// false on overflow, leaves current value and index unchanged.
extern "C" DamnVulnerableDll_API int ProcessImage(char *filename);