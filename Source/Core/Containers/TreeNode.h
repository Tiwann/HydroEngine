#pragma once
#include "Core/Iterator.h"

namespace Hydro
{
    template<class TreeNodeType>
    class TreeNode
    {
    public:
        using TreeNodeIterator = Iterator<TreeNode>;
        using TreeNodeConstIterator = ConstIterator<TreeNode>;
        
        TreeNode() = default;
        TreeNode(const TreeNodeType& Value) : m_Value(Value){}

        TreeNode& AddChild(const TreeNodeType& Child)
        {
            m_Children.push_back({Child});
            TreeNode& ChildNode = m_Children[m_Children.size() - 1];
            ChildNode.m_Parent = this;
            return ChildNode;
        }

        void ForEach(std::function<void(const TreeNode& Node)> Delegate) const
        {
            for (const auto & Child : m_Children)
                Delegate(Child);
        }
        
        bool HasChildren() const { return !m_Children.empty(); }
        bool HasParent() const { return m_Parent; }
        TreeNode& GetParent() const { return *m_Parent; }
        std::vector<TreeNode>& GetChildren() const { return m_Children; }

        bool IsRoot() const { return !HasParent() && !m_Value.has_value(); }

        const TreeNodeType& GetValue() const { return m_Value.value(); }
        
        TreeNodeIterator begin() { return TreeNodeIterator(m_Children.data()); }
        TreeNodeIterator end() { return TreeNodeIterator(m_Children.data() + m_Children.size()); }
        TreeNodeConstIterator begin() const { return TreeNodeConstIterator(const_cast<TreeNode*>(m_Children.data())); }
        TreeNodeConstIterator end() const { return TreeNodeConstIterator(const_cast<TreeNode*>(m_Children.data()) + m_Children.size()); }

    private:
        std::optional<TreeNodeType> m_Value;
        TreeNode* m_Parent = nullptr;
        std::vector<TreeNode> m_Children;
    };
}
