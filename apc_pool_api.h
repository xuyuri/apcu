/*
  +----------------------------------------------------------------------+
  | APC                                                                  |
  +----------------------------------------------------------------------+
  | Copyright (c) 2006-2011 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt.                                 |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Authors: Gopal Vijayaraghavan <gopalv@yahoo-inc.com>                 |
  +----------------------------------------------------------------------+

   This software was contributed to PHP by Yahoo! Inc. in 2008.

   Future revisions and derivatives of this source code must acknowledge
   Yahoo! Inc. as the original contributor of this module by
   leaving this note intact in the source code.

   All other licensing and usage conditions are those of the PHP Group.

 */

#ifndef APC_POOL_API_H
#define APC_POOL_API_H

typedef struct _apc_pool apc_pool;

/* {{{ enum definition: apc_pool_type */
typedef enum {
	APC_SMALL_POOL     = 0x1,
	APC_MEDIUM_POOL    = 0x2,
	APC_LARGE_POOL     = 0x3,
} apc_pool_type; /* }}} */

/* {{{ enum definition: apc_copy_type */
/* APC_COPY_IN should be used when copying into APC
   APC_COPY_OUT should be used when copying out of APC */
typedef enum _apc_copy_type {
	APC_COPY_IN,
	APC_COPY_OUT,
} apc_copy_type; /* }}} */

/* {{{ struct definition: apc_context_t */
typedef struct _apc_context_t {
	apc_pool*          pool;            /* pool of memory for context */
	apc_sma_t*         sma;             /* SMA reference for the pool */
	apc_copy_type      copy;            /* copying type for context */
	HashTable          copied;          /* copied zvals for recursion support */
	apc_serializer_t*  serializer;      /* serializer */
} apc_context_t; /* }}} */

/*
 apc_pool_create creates a pool of the specified type,
 setting the handlers passed on the pool, returns apc_pool*
*/
PHP_APCU_API apc_pool* apc_pool_create(apc_pool_type pool_type, apc_sma_t *sma);

/*
 apc_pool_destroy first calls apc_cleanup_t set during apc_pool_create, then apc_free_t
*/
PHP_APCU_API void apc_pool_destroy(apc_pool *pool, apc_sma_t *sma);

/* Allocate size bytes in the pool */
PHP_APCU_API void *apc_pool_alloc(apc_pool *pool, apc_sma_t *sma, size_t size);

/* Get allocated size of pool */
PHP_APCU_API size_t apc_pool_size(apc_pool *pool);

PHP_APCU_API zend_string* apc_pool_string_dup(apc_pool *pool, apc_sma_t *sma, zend_string *str);
PHP_APCU_API zend_string* apc_pool_string_init(
		apc_pool *pool, apc_sma_t *sma, char *buf, size_t buf_len);

#endif

