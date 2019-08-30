# work

## common
### common
- macros  
secondes: day, week, year

- auto locker  
thread mutex

- methods
get_now: get now time: YYYYMMDDHHMMSS
get_date: get date YYYYMMDD
get_time: get time: YYYYMMDDHHMMSS
is_same_day: check same day
get_week: get week YYYYWW

### utils
- macros
HL_CHECK_RESULT_RETURN_VOID
HL_CHECK_RESULT_RETURN
HL_CHECK_RESULT_EXIT
HL_XFREE

- methods
cp_file: copy file
load_file: load file

## ds
data struct
### single-linked list c-type
hlsl_push_back: add element in single-linked list's back
hlsl_pop_front: pop element from single-linked list's head
hlsl_init_pool: init single-linked list pool
hlsl_get_free_elem_from_pool: get free single-linked list element
hlsl_free_elem_to_pool: free single-linked list element

## test
all test cases

## db - database
### mysql
- macros
HL_SQL_MAX_SIZE

- public methods
connect: connect to mysql
reconnect: reconnect to mysql
query: query mysql
read_options: read options

### mongodb
- static methods
init_mongo: init mongo

- public methods
connect: connect to mongodb
find: query mongodb
read_options: read options

### redis
- macros
HL_REDIS_CMD_MAX_LENGTH

- public methods
connect: connect redis
read_options: read options

## lib
### mmap
get_mmap: get mmap
delete_mmap: delete mmap


