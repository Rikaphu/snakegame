#include "pch.h"
#include "../snake_game/linked_list.cpp"

TEST(linked_list, empty_list_has_size_0) {
	linked_list* list = new linked_list;

	EXPECT_EQ(0, list->get_size());
}

TEST(linked_list, append_element_size_1) {
	linked_list* list = new linked_list;

	list->append(42);

	EXPECT_EQ(1, list->get_size());
}

TEST(linked_list, append_element_get_0) {
	linked_list* list = new linked_list;

	list->append(42);

	EXPECT_EQ(42, list->get(0));
}

TEST(linked_list, append_two_elements) {
	linked_list* list = new linked_list;

	list->append(67);
	list->append(51);

	EXPECT_EQ(2, list->get_size());

	EXPECT_EQ(67, list->get(0));
	EXPECT_EQ(51, list->get(1));
}

TEST(linked_list, append_three_elements) {
	linked_list* list = new linked_list;

	list->append(13);
	list->append(84);
	list->append(20);

	EXPECT_EQ(3, list->get_size());

	EXPECT_EQ(13, list->get(0));
	EXPECT_EQ(84, list->get(1));
	EXPECT_EQ(20, list->get(2));
}

TEST(linked_list, insert_test) {
	linked_list* list = new linked_list;

	list->insert(0, 98);

	EXPECT_EQ(1, list->get_size());

	EXPECT_EQ(98, list->get(0));
}

TEST(linked_list, insert_test_2) {
	linked_list* list = new linked_list;

	list->insert(0, 89);

	list->insert(0, 18);

	EXPECT_EQ(2, list->get_size());

	EXPECT_EQ(18, list->get(0));
	EXPECT_EQ(89, list->get(1));
}

TEST(linked_list, insert_test_3) {
	linked_list* list = new linked_list;
	list->append(42);
	list->append(68);
	list->append(13);

	list->insert(2, 74);

	EXPECT_EQ(4, list->get_size());

	EXPECT_EQ(42, list->get(0));
	EXPECT_EQ(68, list->get(1));
	EXPECT_EQ(74, list->get(2));
	EXPECT_EQ(13, list->get(3));
}

TEST(linked_list, remove_test) {
	linked_list* list = new linked_list;
	list->append(92);

	list->remove(0);

	EXPECT_EQ(0, list->get_size());
}

TEST(linked_list, remove_test_2) {
	linked_list* list = new linked_list;
	list->append(27);
	list->append(63);

	list->remove(0);

	EXPECT_EQ(1, list->get_size());

	EXPECT_EQ(63, list->get(0));
}

TEST(linked_list, remove_test_3) {
	linked_list* list = new linked_list;
	list->append(74);
	list->append(59);
	list->append(33);
	list->append(14);

	list->remove(2);

	EXPECT_EQ(3, list->get_size());

	EXPECT_EQ(74, list->get(0));
	EXPECT_EQ(59, list->get(1));
	EXPECT_EQ(14, list->get(2));
}

TEST(linked_list, contains_empty_list) {
	linked_list* list = new linked_list;

	EXPECT_FALSE(list->contains(10));
}


TEST(linked_list, contains_true) {
	linked_list* list = new linked_list;
	list->append(65);
	list->append(545);
	list->append(321);
	list->append(10);

	EXPECT_TRUE(list->contains(10));
}

TEST(linked_list, contains_false) {
	linked_list* list = new linked_list;
	list->append(65);
	list->append(545);
	list->append(321);
	list->append(10);

	EXPECT_FALSE(list->contains(100));
}