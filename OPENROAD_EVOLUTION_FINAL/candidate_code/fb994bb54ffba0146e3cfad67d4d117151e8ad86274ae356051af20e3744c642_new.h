// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.95183419;
  double density_weight = 0.00298984;
  double prefix_weight = 0.06769653;
  double neighborhood_weight = 0.07234501;
  double late_weight = 0.27486185;
  double critical_weight = 0.17518526;
  unsigned budget = 6;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
