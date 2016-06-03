#include <ext/pb_ds/detail/standard_policies.hpp>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
 
typedef tree <
   string, // Key Type
   null_type, // Mapped type
   less<string>, // Compare functor
   rb_tree_tag, // Tree tag: [rb_tree_tag|splay_tree_tag|ov_tree_tag]
   tree_order_statistics_node_update // Update policy
> ordered_set;

// Extra functions: find_by_order() and order_of_key()
