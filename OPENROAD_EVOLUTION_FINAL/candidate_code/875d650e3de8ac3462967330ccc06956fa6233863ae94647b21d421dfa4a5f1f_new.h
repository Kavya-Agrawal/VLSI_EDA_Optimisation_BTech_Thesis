// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.76317042;
  double density_weight = 0.20734588;
  double prefix_weight = 0.10037735;
  double neighborhood_weight = 0.36118500;
  double late_weight = 0.19490404;
  double critical_weight = 0.30295943;
  unsigned budget = 35;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
