#include <cmath>
#include <cstddef>
#include <limits>
#include <memory>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>
#include <gtest/gtest.h>
#include <entt/core/memory.hpp>
#include "../common/basic_test_allocator.hpp"
#include "../common/config.h"
#include "../common/throwing_allocator.hpp"
#include "../common/throwing_type.hpp"
#include "../common/tracked_memory_resource.hpp"

TEST(ToAddress, Functionalities) {
    const std::shared_ptr<int> shared = std::make_shared<int>();
    auto *plain = std::addressof(*shared);

    ASSERT_EQ(entt::to_address(shared), plain);
    ASSERT_EQ(entt::to_address(plain), plain);
}

TEST(PoccaPocmaAndPocs, Functionalities) {
    test::basic_test_allocator<int> lhs, rhs;
    test::basic_test_allocator<int, std::false_type> no_pocs;

    // code coverage purposes
    ASSERT_FALSE(lhs == rhs);
    ASSERT_NO_THROW(entt::propagate_on_container_swap(no_pocs, no_pocs));

    // honestly, I don't even know how one is supposed to test such a thing :)
    entt::propagate_on_container_copy_assignment(lhs, rhs);
    entt::propagate_on_container_move_assignment(lhs, rhs);
    entt::propagate_on_container_swap(lhs, rhs);
}

ENTT_DEBUG_TEST(PoccaPocmaAndPocsDeathTest, Functionalities) {
    test::basic_test_allocator<int, std::false_type> lhs, rhs;

    ASSERT_DEATH(entt::propagate_on_container_swap(lhs, rhs), "");
}

TEST(IsPowerOfTwo, Functionalities) {
    // constexpr-ness guaranteed
    constexpr auto zero_is_power_of_two = entt::is_power_of_two(0u);

    ASSERT_FALSE(zero_is_power_of_two);
    ASSERT_TRUE(entt::is_power_of_two(1u));
    ASSERT_TRUE(entt::is_power_of_two(2u));
    ASSERT_TRUE(entt::is_power_of_two(4u));
    ASSERT_FALSE(entt::is_power_of_two(7u));
    ASSERT_TRUE(entt::is_power_of_two(128u));
    ASSERT_FALSE(entt::is_power_of_two(200u));
}

TEST(NextPowerOfTwo, Functionalities) {
    // constexpr-ness guaranteed
    constexpr auto next_power_of_two_of_zero = entt::next_power_of_two(0u);

    ASSERT_EQ(next_power_of_two_of_zero, 1u);
    ASSERT_EQ(entt::next_power_of_two(1u), 1u);
    ASSERT_EQ(entt::next_power_of_two(2u), 2u);
    ASSERT_EQ(entt::next_power_of_two(3u), 4u);
    ASSERT_EQ(entt::next_power_of_two(17u), 32u);
    ASSERT_EQ(entt::next_power_of_two(32u), 32u);
    ASSERT_EQ(entt::next_power_of_two(33u), 64u);
    ASSERT_EQ(entt::next_power_of_two(static_cast<std::size_t>(std::pow(2, 16))), static_cast<std::size_t>(std::pow(2, 16)));
    ASSERT_EQ(entt::next_power_of_two(static_cast<std::size_t>(std::pow(2, 16) + 1u)), static_cast<std::size_t>(std::pow(2, 17)));
}

ENTT_DEBUG_TEST(NextPowerOfTwoDeathTest, Functionalities) {
    ASSERT_DEATH(static_cast<void>(entt::next_power_of_two((std::size_t{1u} << (std::numeric_limits<std::size_t>::digits - 1)) + 1)), "");
}

TEST(FastMod, Functionalities) {
    // constexpr-ness guaranteed
    constexpr auto fast_mod_of_zero = entt::fast_mod(0u, 8u);

    ASSERT_EQ(fast_mod_of_zero, 0u);
    ASSERT_EQ(entt::fast_mod(7u, 8u), 7u);
    ASSERT_EQ(entt::fast_mod(8u, 8u), 0u);
}

TEST(AllocateUnique, Functionalities) {
    test::throwing_allocator<test::throwing_type> allocator{};

    allocator.throw_counter<test::throwing_type>(0u);

    ASSERT_THROW((entt::allocate_unique<test::throwing_type>(allocator, false)), test::throwing_allocator_exception);
    ASSERT_THROW((entt::allocate_unique<test::throwing_type>(allocator, test::throwing_type{true})), test::throwing_type_exception);

    std::unique_ptr<test::throwing_type, entt::allocation_deleter<test::throwing_allocator<test::throwing_type>>> ptr = entt::allocate_unique<test::throwing_type>(allocator, false);

    ASSERT_TRUE(ptr);
    ASSERT_EQ(*ptr, false);

    ptr.reset();

    ASSERT_FALSE(ptr);
}

#if defined(ENTT_HAS_TRACKED_MEMORY_RESOURCE)

TEST(AllocateUnique, NoUsesAllocatorConstruction) {
    test::tracked_memory_resource memory_resource{};
    std::pmr::polymorphic_allocator<int> allocator{&memory_resource};

    using type = std::unique_ptr<int, entt::allocation_deleter<std::pmr::polymorphic_allocator<int>>>;
    [[maybe_unused]] const type ptr = entt::allocate_unique<int>(allocator, 0);

    ASSERT_EQ(memory_resource.do_allocate_counter(), 1u);
    ASSERT_EQ(memory_resource.do_deallocate_counter(), 0u);
}

TEST(AllocateUnique, UsesAllocatorConstruction) {
    using string_type = typename test::tracked_memory_resource::string_type;

    test::tracked_memory_resource memory_resource{};
    std::pmr::polymorphic_allocator<string_type> allocator{&memory_resource};

    using type = std::unique_ptr<string_type, entt::allocation_deleter<std::pmr::polymorphic_allocator<string_type>>>;
    [[maybe_unused]] const type ptr = entt::allocate_unique<string_type>(allocator, test::tracked_memory_resource::default_value);

    ASSERT_GT(memory_resource.do_allocate_counter(), 1u);
    ASSERT_EQ(memory_resource.do_deallocate_counter(), 0u);
}

#endif

TEST(UsesAllocatorConstructionArgs, NoUsesAllocatorConstruction) {
    const auto value = 42;
    const auto args = entt::uses_allocator_construction_args<int>(std::allocator<int>{}, value);

    ASSERT_EQ(std::tuple_size_v<decltype(args)>, 1u);
    testing::StaticAssertTypeEq<decltype(args), const std::tuple<const int &>>();
    ASSERT_EQ(std::get<0>(args), value);
}

TEST(UsesAllocatorConstructionArgs, LeadingAllocatorConvention) {
    const auto value = 42;
    const auto args = entt::uses_allocator_construction_args<std::tuple<int, char>>(std::allocator<int>{}, value, 'c');

    ASSERT_EQ(std::tuple_size_v<decltype(args)>, 4u);
    testing::StaticAssertTypeEq<decltype(args), const std::tuple<std::allocator_arg_t, const std::allocator<int> &, const int &, char &&>>();
    ASSERT_EQ(std::get<2>(args), value);
}

TEST(UsesAllocatorConstructionArgs, TrailingAllocatorConvention) {
    const auto size = 42u;
    const auto args = entt::uses_allocator_construction_args<std::vector<int>>(std::allocator<int>{}, size);

    ASSERT_EQ(std::tuple_size_v<decltype(args)>, 2u);
    testing::StaticAssertTypeEq<decltype(args), const std::tuple<const unsigned int &, const std::allocator<int> &>>();
    ASSERT_EQ(std::get<0>(args), size);
}

TEST(UsesAllocatorConstructionArgs, PairPiecewiseConstruct) {
    const auto size = 42u;
    const auto tup = std::make_tuple(size);
    const auto args = entt::uses_allocator_construction_args<std::pair<int, std::vector<int>>>(std::allocator<int>{}, std::piecewise_construct, std::make_tuple(3), tup);

    ASSERT_EQ(std::tuple_size_v<decltype(args)>, 3u);
    testing::StaticAssertTypeEq<decltype(args), const std::tuple<std::piecewise_construct_t, std::tuple<int &&>, std::tuple<const unsigned int &, const std::allocator<int> &>>>();
    ASSERT_EQ(std::get<0>(std::get<2>(args)), size);
}

TEST(UsesAllocatorConstructionArgs, PairNoArgs) {
    [[maybe_unused]] const auto args = entt::uses_allocator_construction_args<std::pair<int, std::vector<int>>>(std::allocator<int>{});

    ASSERT_EQ(std::tuple_size_v<decltype(args)>, 3u);
    testing::StaticAssertTypeEq<decltype(args), const std::tuple<std::piecewise_construct_t, std::tuple<>, std::tuple<const std::allocator<int> &>>>();
}

TEST(UsesAllocatorConstructionArgs, PairValues) {
    const auto size = 42u;
    const auto args = entt::uses_allocator_construction_args<std::pair<int, std::vector<int>>>(std::allocator<int>{}, 3, size);

    ASSERT_EQ(std::tuple_size_v<decltype(args)>, 3u);
    testing::StaticAssertTypeEq<decltype(args), const std::tuple<std::piecewise_construct_t, std::tuple<int &&>, std::tuple<const unsigned int &, const std::allocator<int> &>>>();
    ASSERT_EQ(std::get<0>(std::get<2>(args)), size);
}

TEST(UsesAllocatorConstructionArgs, PairConstLValueReference) {
    const auto value = std::make_pair(3, 42u);
    const auto args = entt::uses_allocator_construction_args<std::pair<int, std::vector<int>>>(std::allocator<int>{}, value);

    ASSERT_EQ(std::tuple_size_v<decltype(args)>, 3u);
    testing::StaticAssertTypeEq<decltype(args), const std::tuple<std::piecewise_construct_t, std::tuple<const int &>, std::tuple<const unsigned int &, const std::allocator<int> &>>>();
    ASSERT_EQ(std::get<0>(std::get<1>(args)), 3);
    ASSERT_EQ(std::get<0>(std::get<2>(args)), 42u);
}

TEST(UsesAllocatorConstructionArgs, PairRValueReference) {
    [[maybe_unused]] const auto args = entt::uses_allocator_construction_args<std::pair<int, std::vector<int>>>(std::allocator<int>{}, std::make_pair(3, 42u));

    ASSERT_EQ(std::tuple_size_v<decltype(args)>, 3u);
    testing::StaticAssertTypeEq<decltype(args), const std::tuple<std::piecewise_construct_t, std::tuple<int &&>, std::tuple<unsigned int &&, const std::allocator<int> &>>>();
}

TEST(MakeObjUsingAllocator, Functionalities) {
    const auto size = 42u;
    test::throwing_allocator<int> allocator{};

    allocator.throw_counter<int>(0u);

    ASSERT_THROW((entt::make_obj_using_allocator<std::vector<int, test::throwing_allocator<int>>>(allocator, size)), test::throwing_allocator_exception);

    const auto vec = entt::make_obj_using_allocator<std::vector<int>>(std::allocator<int>{}, size);

    ASSERT_FALSE(vec.empty());
    ASSERT_EQ(vec.size(), size);
}

TEST(UninitializedConstructUsingAllocator, NoUsesAllocatorConstruction) {
    alignas(int) std::byte storage[sizeof(int)]; // NOLINT
    const std::allocator<int> allocator{};

    int *value = entt::uninitialized_construct_using_allocator(reinterpret_cast<int *>(&storage), allocator, 1); // NOLINT

    ASSERT_EQ(*value, 1);
}

#if defined(ENTT_HAS_TRACKED_MEMORY_RESOURCE)
#    include <memory_resource>

TEST(UninitializedConstructUsingAllocator, UsesAllocatorConstruction) {
    using string_type = typename test::tracked_memory_resource::string_type;

    test::tracked_memory_resource memory_resource{};
    const std::pmr::polymorphic_allocator<string_type> allocator{&memory_resource};
    alignas(string_type) std::byte storage[sizeof(string_type)]; // NOLINT

    string_type *value = entt::uninitialized_construct_using_allocator(reinterpret_cast<string_type *>(&storage), allocator, test::tracked_memory_resource::default_value); // NOLINT

    ASSERT_GT(memory_resource.do_allocate_counter(), 0u);
    ASSERT_EQ(memory_resource.do_deallocate_counter(), 0u);
    ASSERT_EQ(*value, test::tracked_memory_resource::default_value);

    value->~string_type();
}

#endif
