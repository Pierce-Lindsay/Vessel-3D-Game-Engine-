#include "pch.h"
#include "Core/objects/Object.h"
#include "Core/utils/VectorMap.h"
#include "Core/components/Transformer.h"
#include "Core/components/Hierarchy.h"
#include "TestScene.h"

TEST(Hierarchy, removeAddChildren) {
	ve::Object obj("o1");
	ve::Object obj2("o2");
	ve::Object obj3("o3");
	ve::Object obj4("o4");
	ve::Object obj5("o5");
	ve::Object obj6("o6");
	std::vector<ve::Object*> childs = { &obj2, &obj3, &obj4 };
	std::vector<ve::Object*> childs2 = { &obj6 };

	ve::Hierarchy h(nullptr, childs, &obj5);
	ve::Hierarchy h2(nullptr, childs2);
	ASSERT_TRUE(h.getChildren().size() == 3);
	EXPECT_EQ(h.getChild(obj2.getID())->getID(), obj2.getID());
	EXPECT_EQ(h.getChild(obj3.getID())->getID(), obj3.getID());
	EXPECT_EQ(h.getChild(obj4.getID())->getID(), obj4.getID());
	EXPECT_EQ(h.getChild(obj5.getID() + 1), nullptr);
	EXPECT_EQ(h.getParent()->getID(), obj5.getID());
	h.removeChild(obj3.getID());
	ASSERT_TRUE(h.getChildren().size() == 2);
	EXPECT_EQ(h.getChild(obj3.getID()), nullptr);
	EXPECT_EQ(h.removeChild(obj3.getID()), -1);
	h2.removeChild(obj6.getID());
	ASSERT_TRUE(h2.getChildren().size() == 0);
	EXPECT_EQ(h2.getChild(obj6.getID()), nullptr);
}

TEST(VectorMap, createObjectTypes) {

	ve::VectorMap<std::type_index, ve::Component> map;
	auto transPtr = std::make_unique<ve::Transformer>(nullptr, glm::vec3(2.f, 1.f, 6.f));
	auto hierPtr = std::make_unique<ve::Hierarchy>(nullptr);
	map.add(typeid(ve::Transformer), std::move(transPtr));
	map.add(typeid(ve::Hierarchy), std::move(hierPtr));

	auto v1 = map.get(typeid(ve::Transformer));
	auto v2 = map.get(typeid(ve::Hierarchy));
	EXPECT_EQ(v1->getType(), "transformer");
	EXPECT_EQ(v2->getType(), "hierarchy");
	EXPECT_EQ(1, 1);
}

TEST(VectorMap, removeObjectTypes) {

	ve::VectorMap<std::type_index, ve::Component> map;
	auto transPtr = std::make_unique<ve::Transformer>(nullptr, glm::vec3(2.f, 1.f, 6.f));
	auto hierPtr = std::make_unique<ve::Hierarchy>(nullptr);
	map.add(typeid(ve::Transformer), std::move(transPtr));
	map.add(typeid(ve::Hierarchy), std::move(hierPtr));

	int r = map.remove(typeid(ve::Transformer));
	int r2 = map.remove(typeid(ve::Transformer));
	auto v1 = map.get(typeid(ve::Transformer));
	auto v2 = map.get(typeid(ve::Hierarchy));
	bool c1 = map.contains(typeid(ve::Transformer));
	bool c2 = map.contains(typeid(ve::Hierarchy));
	EXPECT_EQ(v1, nullptr);
	EXPECT_EQ(v2->getType(), "hierarchy");
	EXPECT_EQ(r, 0);
	EXPECT_EQ(r2, -1);
	EXPECT_EQ(c1, false);
	EXPECT_EQ(c2, true);
}

TEST(VectorMap, oneOfObjectTypes) {

	ve::VectorMap<std::type_index, ve::Component> map;
	glm::vec3 pos1{ 1,1, 1 };
	auto transPtr = std::make_unique<ve::Transformer>(nullptr, glm::vec3(2.f, 1.f, 6.f));
	auto trans2Ptr = std::make_unique<ve::Transformer>(nullptr, pos1);
	auto hierPtr = std::make_unique<ve::Hierarchy>(nullptr);
	map.add(typeid(ve::Transformer), std::move(transPtr));
	map.add(typeid(ve::Hierarchy), std::move(hierPtr));
	map.add(typeid(ve::Transformer), std::move(trans2Ptr));

	ve::Transformer* v1 = dynamic_cast<ve::Transformer*>(map.get(typeid(ve::Transformer)));
	auto v2 = map.get(typeid(ve::Hierarchy));
	EXPECT_EQ(v2->getType(), "hierarchy");
	EXPECT_EQ(v1->getType(), "transformer");
	EXPECT_EQ(v1->getPos(), pos1);
}

TEST(Object, objectCreate) {

	ve::Object obj("hello");
	ve::Object obj2("world");

	EXPECT_EQ(obj.getType(), "hello");
	EXPECT_EQ(obj2.getType(), "world");
	obj2.setType("world2");
	EXPECT_EQ(obj2.getType(), "world2");
	EXPECT_EQ(obj2.getComponent<ve::Transformer>(), nullptr);
}

TEST(Object, objectAddComponents) {

	ve::Object obj("hello");
	ve::Object obj2("world");
	ve::Object obj3("world2");
	ve::Object obj4("world3");

	glm::vec3 pos1{ 1,1, 1 };
	glm::vec3 pos2{ 1,2, 1 };
	obj.addComponent<ve::Transformer>(pos1);
	obj2.addComponent<ve::Transformer>(pos2);
	std::vector<ve::Object*> children;
	std::vector<ve::Object*> children2;
	children.push_back(&obj3);
	children.push_back(&obj4);
	obj2.addComponent<ve::Hierarchy>(children);
	obj3.addComponent<ve::Hierarchy>(children2, &obj2);
	obj4.addComponent<ve::Hierarchy>(children2, &obj2);

	EXPECT_EQ(obj.getComponent<ve::Hierarchy>(), nullptr);
	EXPECT_EQ(obj.getComponent<ve::Transformer>()->getPos(), pos1);
	EXPECT_EQ(obj2.getComponent<ve::Transformer>()->getPos(), pos2);
	ASSERT_TRUE(obj2.getComponent<ve::Hierarchy>() != nullptr);
	auto childs = obj2.getComponent<ve::Hierarchy>()->getChildren();
	ASSERT_TRUE(childs.size() == 2);
	EXPECT_EQ(childs[0]->getType(), "world2");
	EXPECT_EQ(childs[1]->getType(), "world3");
	EXPECT_EQ(obj3.getComponent<ve::Hierarchy>()->getParent()->getType(), "world");
	EXPECT_EQ(obj4.getComponent<ve::Hierarchy>()->getParent()->getType(), "world");
}

TEST(Scene, addAndRemove) {

	TestScene ts;
	ts.startup();
	const auto& objs = ts.getObjects();
	ASSERT_TRUE(objs.size() == 3);
	EXPECT_EQ(ts.getObject(ts.obj1->getID())->getID(), ts.obj1->getID());
	EXPECT_EQ(ts.getObject(ts.obj2->getID())->getID(), ts.obj2->getID());
	EXPECT_EQ(ts.getObject(ts.obj3->getID())->getID(), ts.obj3->getID());
	auto id = ts.obj2->getID();
	ts.lazyDeleteObject(ts.obj2); //request delete
	EXPECT_EQ(ts.obj2->getMarkedForDeletion(), true);
	ts.update(); //deletes
	ASSERT_TRUE(objs.size() == 2);
	EXPECT_EQ(ts.getObject(ts.obj3->getID())->getID(), ts.obj3->getID());
	EXPECT_EQ(ts.getObject(ts.obj1->getID())->getID(), ts.obj1->getID());
	EXPECT_EQ(ts.getObject(id), nullptr);
}
