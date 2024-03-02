set(ALL_CXX_WARNING_FLAGS
--all-warnings
--extra-warnings
-W
-Waddress
-Waggregate-return
-Waggressive-loop-optimizations
-Wall
-Walloca
-Walloc-zero
-Wattributes
-Wbool-compare
-Wbool-operation
-Wbuiltin-declaration-mismatch
-Wbuiltin-macro-redefined
-Wdangling-else
-Wdate-time
-Wdelete-incomplete
-Wdelete-non-virtual-dtor
-Wdeprecated
-Wdeprecated-declarations
-Wdisabled-optimization
-Wdiv-by-zero
-Wdouble-promotion
-Wduplicated-branches
-Wduplicated-cond
-Weffc++
-Wempty-body
-Wendif-labels
-Wenum-compare
-Werror
-Wexpansion-to-defined
-Wextra
-Wfloat-conversion
-Wfloat-equal
-Wframe-address
-Wfree-nonheap-object
-Whsa
-Wignored-attributes
-Wignored-qualifiers
-Winherited-variadic-ctor
-Winit-self
-Winline
## We've changed Winline from OFF to ON after all
-Winline
-Wint-in-bool-context
-Wint-to-pointer-cast
-Winvalid-memory-model
-Winvalid-offsetof
-Winvalid-pch
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
-Wmissing-braces
-Wmissing-declarations
-Wmissing-field-initializers
-Wmissing-format-attribute
-Wmissing-include-dirs
-Wmissing-noreturn
-Wmultichar
-Wmultiple-inheritance
-Wnamespaces
-Wnarrowing
-Wnoexcept
-Wnoexcept-type
-Wnonnull
-Wnonnull-compare
-Wnon-template-friend
-Wnon-virtual-dtor
-Wnull-dereference
-Wodr
-Wold-style-cast
-Wopenmp-simd
-Woverflow
-Woverlength-strings
-Woverloaded-virtual
-Wpacked
-Wpacked-bitfield-compat
-Wpadded
-Wparentheses
-Wpedantic
-Wpmf-conversions
-Wpointer-arith
-Wpointer-compare
-Wpragmas
-Wpsabi
-Wredundant-decls
-Wregister
-Wreorder
-Wrestrict
-Wreturn-local-addr
-Wreturn-type
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
-Wsizeof-pointer-memaccess
-Wstack-protector
-Wstrict-null-sentinel
-Wsubobject-linkage
-Wsuggest-attribute=const
-Wsuggest-attribute=format
-Wsuggest-attribute=noreturn
-Wsuggest-attribute=pure
-Wsuggest-final-methods
-Wsuggest-final-types
-Wsuggest-override
-Wswitch
-Wswitch-bool
-Wswitch-default
-Wswitch-enum
-Wswitch-unreachable
-Wsync-nand
-Wsynth
-Wsystem-headers
-Wtautological-compare
-Wtemplates
-Wterminate
-Wtrampolines
-Wtrigraphs
-Wtype-limits
-Wundef
-Wuninitialized
-Wunknown-pragmas
-Wunreachable-code
-Wunsafe-loop-optimizations
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
-Wuseless-cast
-Wvarargs
-Wvariadic-macros
-Wvector-operation-performance
-Wvirtual-inheritance
-Wvirtual-move-assign
-Wvla
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
-Wno-long-long
-Wno-psabi
-Wdate-time
)

#STRING(REPLACE ";" " " ALL_CXX_WARNING_FLAGS "${ALL_CXX_WARNING_FLAGS}")
