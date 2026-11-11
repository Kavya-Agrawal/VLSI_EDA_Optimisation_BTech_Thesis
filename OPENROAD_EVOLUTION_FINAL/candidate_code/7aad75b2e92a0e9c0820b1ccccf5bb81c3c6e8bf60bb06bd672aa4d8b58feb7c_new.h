// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.48142995;
  double density_weight = 0.08082593;
  double prefix_weight = 0.16284775;
  double neighborhood_weight = 0.30310102;
  double late_weight = 0.21242929;
  double critical_weight = 0.09805994;
  unsigned budget = 14;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
