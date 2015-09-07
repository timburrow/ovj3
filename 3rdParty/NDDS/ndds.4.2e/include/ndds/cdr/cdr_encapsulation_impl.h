/*
 * @(#)cdr_encapsulation_impl.h    generated by: makeheader    Mon Dec  3 23:08:01 2007
 *
 *		built from:	encapsulation_impl.ifc
 */

#ifndef cdr_encapsulation_impl_h
#define cdr_encapsulation_impl_h


#ifdef __cplusplus
    extern "C" {
#endif



#define RTICdrEncapsulation_validCdrEncapsulation(_id, _opts, _sopts) \
((_id) == RTI_CDR_ENCAPSULATION_ID_CDR_BE ? RTI_TRUE : \
(_id) == RTI_CDR_ENCAPSULATION_ID_CDR_LE)

#define RTICdrEncapsulation_validParameterCdrEncapsulation(_id, _opts, _sopts) \
((_id) == RTI_CDR_ENCAPSULATION_ID_PL_CDR_BE ? RTI_TRUE : \
(_id) == RTI_CDR_ENCAPSULATION_ID_PL_CDR_LE)
            


#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* cdr_encapsulation_impl_h */