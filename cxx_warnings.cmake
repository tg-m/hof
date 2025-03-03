set(ALL_CXX_WARNING_FLAGS
--all-warnings
--extra-warnings
-W

-WNSObject-attribute

## -Wabi ## C/ObjC
## -Wabsolute-value ## C/ObjC
-Waddress
-Waddress-of-packed-member
-Waggregate-return
-Waggressive-loop-optimizations
-Wall
-Walloca
-Walloc-size
-Walloc-zero
-Wanalyzer-allocation-size
-Wanalyzer-deref-before-check
-Wanalyzer-double-fclose
-Wanalyzer-double-free
-Wanalyzer-exposure-through-output-file
-Wanalyzer-exposure-through-uninit-copy
-Wanalyzer-fd-access-mode-mismatch
-Wanalyzer-fd-double-close
-Wanalyzer-fd-leak
-Wanalyzer-fd-phase-mismatch
-Wanalyzer-fd-type-mismatch
-Wanalyzer-fd-use-after-close
-Wanalyzer-fd-use-without-check
-Wanalyzer-file-leak
-Wanalyzer-free-of-non-heap
-Wanalyzer-imprecise-fp-arithmetic
-Wanalyzer-infinite-loop
-Wanalyzer-infinite-recursion
-Wanalyzer-jump-through-null
-Wanalyzer-malloc-leak
-Wanalyzer-mismatching-deallocation
-Wanalyzer-null-argument
-Wanalyzer-null-dereference
-Wanalyzer-out-of-bounds
-Wanalyzer-overlapping-buffers
-Wanalyzer-possible-null-argument
-Wanalyzer-possible-null-dereference
-Wanalyzer-putenv-of-auto-var
-Wanalyzer-shift-count-negative
-Wanalyzer-shift-count-overflow
-Wanalyzer-stale-setjmp-buffer
-Wanalyzer-symbol-too-complex
-Wanalyzer-tainted-allocation-size
-Wanalyzer-tainted-array-index
-Wanalyzer-tainted-assertion
-Wanalyzer-tainted-divisor
-Wanalyzer-tainted-offset
-Wanalyzer-tainted-size
-Wanalyzer-too-complex
-Wanalyzer-undefined-behavior-strtok
-Wanalyzer-unsafe-call-within-signal-handler
-Wanalyzer-use-after-free
-Wanalyzer-use-of-pointer-in-stale-stack-frame
-Wanalyzer-use-of-uninitialized-value
-Wanalyzer-va-arg-type-mismatch
-Wanalyzer-va-list-exhausted
-Wanalyzer-va-list-leak
-Wanalyzer-va-list-use-after-va-end
-Wanalyzer-write-to-const
-Wanalyzer-write-to-string-literal
-Warith-conversion
-Warray-compare
-Wattribute-warning
-Wattributes
## -Wbad-function-cast ## C/ObjC
-Wbool-compare
-Wbool-operation
-Wbuiltin-declaration-mismatch
-Wbuiltin-macro-redefined
## -Wc++-compat ## C/ObjC
-Wcalloc-transposed-args
-Wcannot-profile
-Wcast-align
-Wcast-align=strict
-Wcast-function-type
-Wcast-qual
-Wchar-subscripts
-Wclobbered
-Wcomment
## -Wcompare-distinct-pointer-types ## C/ObjC
-Wcomplain-wrong-lang
-Wconversion
-Wcoverage-invalid-line-number
-Wcoverage-mismatch
-Wcoverage-too-many-conditions
-Wcpp
-Wdangling-else
-Wdate-time
-Wdelete-incomplete
-Wdelete-non-virtual-dtor
## -Wdeclaration-missing-parameter-type ## C/ObjC
-Wdeprecated
-Wdeprecated-declarations
## -Wdesignated-init ## C/ObjC
-Wdisabled-optimization
## -Wdiscarded-array-qualifiers ## C/ObjC
## -Wdiscarded-qualifiers ## C/ObjC
-Wdiv-by-zero
-Wdouble-promotion
## -Wduplicate-decl-specifier ## C/ObjC
-Wduplicated-branches
-Wduplicated-cond
-Weffc++
-Wempty-body
-Wendif-labels
-Wenum-compare
-Wenum-conversion
## -Wenum-int-mismatch ## C/ObjC
-Werror
-Wexpansion-to-defined
-Wextra
-Wflex-array-member-not-at-end
-Wfloat-conversion
-Wfloat-equal
-Wformat-contains-nul
-Wformat-diag
-Wformat-extra-args
-Wformat-nonliteral
-Wformat-security
-Wformat-signedness
-Wformat-y2k
-Wformat-zero-length
-Wframe-address
-Wfree-nonheap-object
-Whardened
-Whsa
-Wif-not-aligned
-Wignored-attributes
-Wignored-qualifiers
-Winherited-variadic-ctor
## -Wimplicit ## C/ObjC
## -Wincompatible-pointer-types ## C/ObjC
-Winfinite-recursion
-Winit-self
-Winline
## We've changed Winline from OFF to ON after all
-Winline
## -Wint-conversion ## C/ObjC
-Wint-in-bool-context
-Wint-to-pointer-cast
-Winvalid-memory-model
-Winvalid-offsetof
-Winvalid-pch
-Winvalid-utf8
## -Wjump-misses-init ## C/ObjC
-Wliteral-suffix
-Wlogical-not-parentheses
-Wlogical-op
-Wlong-long
-Wlto-type-mismatch
-Wmain
-Wmaybe-uninitialized
-Wmemset-elt-size
-Wmemset-transposed-args
-Wmisleading-indentation
-Wmismatched-dealloc
-Wmissing-attributes
-Wmissing-braces
-Wmissing-declarations
-Wmissing-field-initializers
-Wmissing-format-attribute
-Wmissing-include-dirs
-Wmissing-noreturn
## -Wmissing-parameter-type ## C/ObjC
-Wmissing-profile
## -Wmissing-prototypes ## C/ObjC
## -Wmissing-variable-declarations ## C/ObjC
-Wmultichar
-Wmultiple-inheritance
-Wnamespaces
-Wnarrowing
-Wnoexcept
-Wnoexcept-type
-Wmultistatement-macros
## -Wnested-externs ## C/ObjC
-Wnonnull
-Wnonnull-compare
-Wnon-template-friend
-Wnon-virtual-dtor
-Wnull-dereference
-Wodr
-Wold-style-cast
## -Wold-style-declaration ## C/ObjC
-Wopenacc-parallelism
-Wopenmp
-Wopenmp-simd
-Woverflow
-Woverlength-strings
-Woverloaded-virtual
## -Woverride-init ## C/ObjC
## -Woverride-init-side-effects ## C/ObjC
-Wpacked
-Wpacked-bitfield-compat
-Wpacked-not-aligned
-Wpadded
-Wparentheses
-Wpedantic
-Wpmf-conversions
-Wpointer-arith
-Wpointer-compare
## -Wpointer-sign ## C/ObjC
## -Wpointer-to-int-cast ## C/ObjC
-Wpragmas
-Wprio-ctor-dtor
-Wpsabi
-Wredundant-decls
-Wregister
-Wreorder
-Wrestrict
-Wreturn-local-addr
-Wreturn-type
## -Wreturn-mismatch ## C/ObjC
-Wscalar-storage-order
-Wsequence-point
-Wshadow
-Wshadow=compatible-local
-Wshadow-compatible-local
-Wshadow=global
-Wshadow=local
-Wshadow-local
-Wshift-count-negative
-Wshift-count-overflow
-Wshift-negative-value
-Wsign-compare
-Wsign-conversion
-Wsign-promo
-Wsized-deallocation
-Wsizeof-array-argument
-Wsizeof-array-div
-Wsizeof-pointer-div
-Wsizeof-pointer-memaccess
-Wstack-protector
-Wstrict-null-sentinel
-Wsubobject-linkage
## -Wstrict-flex-arrays ## C/ObjC
## -Wstrict-prototypes ## C/ObjC
-Wstring-compare
-Wstringop-overread
-Wstringop-truncation
-Wsuggest-attribute=cold
-Wsuggest-attribute=const
-Wsuggest-attribute=format
-Wsuggest-attribute=malloc
-Wsuggest-attribute=noreturn
-Wsuggest-attribute=pure
-Wsuggest-attribute=returns_nonnull
-Wsuggest-final-methods
-Wsuggest-final-types
-Wsuggest-override
-Wswitch
-Wswitch-bool
-Wswitch-default
-Wswitch-enum
-Wswitch-outside-range
-Wswitch-unreachable
-Wsync-nand
-Wsynth
-Wsystem-headers
-Wtautological-compare
-Wtemplates
-Wterminate
## -Wtraditional ## C/ObjC
## -Wtraditional-conversion ## C/ObjC
-Wtrampolines
-Wtrigraphs
-Wtrivial-auto-var-init
-Wtsan
-Wtype-limits
-Wundef
-Wunicode
-Wuninitialized
-Wunknown-pragmas
-Wunreachable-code
-Wunsafe-loop-optimizations
## -Wunsuffixed-float-constants ## C/ObjC
-Wunused
-Wunused-but-set-parameter
-Wunused-but-set-variable
-Wunused-function
-Wunused-label
-Wunused-local-typedefs
-Wunused-macros
-Wunused-parameter
-Wunused-result
-Wunused-value
-Wunused-variable
-Wuse-after-free
-Wuseless-cast
-Wvarargs
-Wvariadic-macros
-Wvector-operation-performance
-Wvirtual-inheritance
-Wvirtual-move-assign
-Wvla
-Wvla-parameter
-Wvolatile-register-var
-Wwrite-strings
-Wzero-as-null-pointer-constant
-Wno-system-headers
-Wno-aggregate-return
-Wno-namespaces
-Wno-templates
-Wno-padded
-Wno-suggest-attribute=const
-Wno-suggest-attribute=pure
-Wno-suggest-attribute=noreturn
-Wno-suggest-attribute=format
--pedantic-errors
-Wnormalized=nfkc
-Waligned-new=all
-Warray-bounds
-Wcast-align
-Wcast-qual
-Wchar-subscripts
-Wclobbered
-Wcomment
-Wconversion
-Wctor-dtor-privacy
-Wformat
-Wformat-nonliteral
-Wformat-security
-Wformat-y2k
-Wstrict-aliasing=3
-Wstrict-overflow=5
-Waligned-new=all
-Wplacement-new=2
-Warray-bounds=2
-Wformat-overflow=2
-Wformat-truncation=2
-Wformat=2
-Wimplicit-fallthrough=5
-Wstringop-overflow=4
-Wunused-const-variable=2
-Wxor-used-as-pow
-Wzero-length-bounds



-Wno-long-long
-Wno-psabi
-Wdate-time
)

#STRING(REPLACE ";" " " ALL_CXX_WARNING_FLAGS "${ALL_CXX_WARNING_FLAGS}")
